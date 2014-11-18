#include "httpserver.hpp"

#include <QtNetwork/QTcpSocket>
#include <QtCore/QTextCodec>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "qtcoroutine.hpp"

namespace {

void sendResponse (QTextStream & sio, const QByteArray & data) {
    auto line = sio.readLine();
    auto parts = line.split(" ");
    auto method = parts[0];
    auto rawResource = parts[1];
    auto protocol = parts[2];

    QUrl resource(rawResource);
    QUrlQuery query(resource);

    qDebug() << method << resource.path() << query.queryItems();

    sio << protocol << " 200 OK\r\n";
    sio << "Content-Type: text/plain; charset=\"utf-8\"\r\n";
    sio << "Content-Length: " << data.size() << "\r\n";
    sio << "\r\n";
    sio << data;
}

QByteArray get (const QtYield & yield, const QString & surl) {
    QNetworkAccessManager nasm;
    QUrl url(surl);
    QNetworkRequest request(url);

    auto reply = nasm.get(request);
    // NOTE yield to main event loop until request finished
    yield(reply, SIGNAL(finished()));

    // follow 301/302 redirection
    auto a = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    while (a.isValid()) {
        QUrl target = a.toUrl();
        qDebug() << "redirect to" << target;
        if (target.isRelative()) {
            target = url.resolved(target);
        }
        request.setUrl(target);

        reply->deleteLater();
        reply = nasm.get(request);
        // NOTE yield to main event loop until request finished
        yield(reply, SIGNAL(finished()));

        a = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    }

    auto data = reply->readAll();
    reply->deleteLater();
    return data;
}

}

HttpServer::HttpServer(QObject *parent) :
    QObject(parent),
    _server(new QTcpServer(this))
{
    this->connect(this->_server, SIGNAL(newConnection()), SLOT(_onNewConnection()));
}

bool HttpServer::listen(quint16 port) {
    return this->_server->listen(QHostAddress::LocalHost, port);
}

void HttpServer::_onNewConnection() {
    while (this->_server->hasPendingConnections()) {
        auto socket = this->_server->nextPendingConnection();
        this->connect(socket, SIGNAL(readyRead()), SLOT(_onClientReadyRead()));
        this->connect(socket, SIGNAL(disconnected()), SLOT(_onClientDisconnected()));
    }
}

void HttpServer::_onClientReadyRead() {
    auto socket = qobject_cast<QTcpSocket *>(this->sender());

    QtCoroutine * task = new QtCoroutine([=](const QtYield & yield)->void {
        // NOTE you can pass `yield` to any function
        auto data = get(yield, "https://www.google.com/");

        QTextStream sio(socket);
        sio.setCodec(QTextCodec::codecForName("UTF-8"));
        sendResponse(sio, data);
        socket->close();
    });
    task->connect(task, SIGNAL(finished()), SLOT(deleteLater()));
    task->start();
}

void HttpServer::_onClientDisconnected() {
    auto socket = qobject_cast<QTcpSocket *>(this->sender());
    socket->deleteLater();
    this->_server->close();
}

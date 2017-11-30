#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <QtCore/QtDebug>

#include "qtael.hpp"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    auto b = new qtael::Async([](const qtael::Await & await)->void {
        QNetworkAccessManager nasm;
        QUrl url("http://www.google.com/");
        QNetworkRequest request(url);
        request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

        auto reply = nasm.get(request);
        qDebug() << "GET http://www.google.com/";
        // NOTE yield to main event loop until request finished
        auto rv = await(reply, &QNetworkReply::redirected);
        qDebug() << std::get<0>(rv);
        await(reply, &QNetworkReply::finished);

        auto data = reply->readAll();
        reply->deleteLater();

        qDebug() << data;
    });
    // NOTE when coroutine finished (i.e. reaches end or return), `finished()` emitted
    b->connect(b, SIGNAL(finished()), SLOT(deleteLater()));
    a.connect(b, SIGNAL(finished()), SLOT(quit()));
    b->start();

    return a.exec();
}

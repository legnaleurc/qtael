#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <QtCore/QtDebug>

#include "qtael.hpp"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    auto b = new qtael::Async([](const qtael::Await & await) -> void {
        QNetworkAccessManager nasm;
        QUrl url("http://www.google.com/");
        QNetworkRequest request(url);

        auto reply = nasm.get(request);
        qDebug() << "GET http://www.google.com/";
        // NOTE yield to main event loop until request finished
        await(reply, &QNetworkReply::finished);

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
            await(reply, &QNetworkReply::finished);

            a = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        }

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

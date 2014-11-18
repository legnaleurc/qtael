#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>

#include "jobqueue.hpp"

int main (int argc, char * argv[]) {
    QCoreApplication app(argc, argv);

    JobQueue jq;

    auto a = jq.setTimeout(1000, [&](const QtYield & yield)->void {
        qDebug() << "A: run callback";
        yield(1000);
        qDebug() << "A: first";
        yield(1000);
        qDebug() << "A: second";
        yield(1000);
        qDebug() << "A: third";
    });

    auto b = jq.setTimeout(1500, [&](const QtYield & yield)->void {
        qDebug() << "B: run callback";
        yield(1000);
        qDebug() << "B: first";
        yield(1000);
        qDebug() << "B: second";
        yield(1000);
        qDebug() << "B: third";
    });

    auto c = jq.setTimeout(2000, [&](const QtYield & yield)->void {
        qDebug() << "C: run callback";
        app.quit();
    });

    auto d = new QtCoroutine([&](const QtYield & yield)->void {
        yield(2500);
        qDebug() << "D: run callback";
        jq.clear(b);
    });
    d->connect(d, SIGNAL(finished()), SLOT(deleteLater()));
    d->start();

    return app.exec();
}

#include <QtCore/QCoreApplication>

#include <QtCore/QtDebug>

#include "jobqueue.hpp"


int main (int argc, char * argv[]) {
    QCoreApplication app(argc, argv);

    JobQueue jq;

    auto a = jq.setTimeout(1000, [&](const qtael::Await & await)->void {
        qDebug() << "A: run callback";
        await(1000);
        qDebug() << "A: first";
        await(1000);
        qDebug() << "A: second";
        await(1000);
        qDebug() << "A: third";
    });

    auto b = jq.setTimeout(1500, [&](const qtael::Await & await)->void {
        qDebug() << "B: run callback";
        await(1000);
        qDebug() << "B: first";
        await(1000);
        qDebug() << "B: second";
        await(1000);
        qDebug() << "B: third";
    });

    auto c = jq.setTimeout(2000, [&](const qtael::Await & /*await*/)->void {
        qDebug() << "C: run callback";
        app.quit();
    });

    auto d = new qtael::Async([&](const qtael::Await & await)->void {
        await(2500);
        qDebug() << "D: run callback";
        jq.clear(b);
    });
    d->connect(d, SIGNAL(finished()), SLOT(deleteLater()));
    d->start();

    return app.exec();
}

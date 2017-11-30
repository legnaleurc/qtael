#include <QtCore/QCoreApplication>

#include <QtCore/QtDebug>

#include "jobqueue.hpp"


int main (int argc, char * argv[]) {
    QCoreApplication app(argc, argv);

    JobQueue jq;

    jq.setTimeout(1000, [&](const qtael::Await & await) -> void {
        qDebug() << "A: run callback";
        await(1000);
        qDebug() << "A: first";
        await(1000);
        qDebug() << "A: second";
        await(1000);
        qDebug() << "A: third";
    });

    jq.setTimeout(1500, [&](const qtael::Await & await) -> void {
        qDebug() << "B: run callback";
        await(1000);
        qDebug() << "B: first";
        await(1000);
        qDebug() << "B: second";
        await(1000);
        qDebug() << "B: third";
    });

    jq.setTimeout(2000, [&](const qtael::Await & /*await*/) -> void {
        qDebug() << "C: run callback";
        app.quit();
    });

    return app.exec();
}

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>

#include "jobqueue.hpp"

int main (int argc, char * argv[]) {
    QCoreApplication app(argc, argv);

    JobQueue jq;

    jq.setTimeout(1000, [&](const QtYield & yield)->void {
        qDebug() << "A: run callback";
        yield(1000);
        qDebug() << "A: first";
        yield(1000);
        qDebug() << "A: second";
        yield(1000);
        qDebug() << "A: third";
    });

    jq.setTimeout(1500, [&](const QtYield & yield)->void {
        qDebug() << "B: run callback";
        yield(1000);
        qDebug() << "B: first";
        yield(1000);
        qDebug() << "B: second";
        yield(1000);
        qDebug() << "B: third";
    });

    jq.setTimeout(2000, [&](const QtYield & yield)->void {
        qDebug() << "C: run callback";
        app.quit();
    });

    return app.exec();
}

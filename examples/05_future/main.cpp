#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QCoreApplication>
#include <QtCore/QFutureWatcher>
#include <QtCore/QThread>

#include <QtCore/QtDebug>

#include "qtcoroutine.hpp"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    auto future = QtConcurrent::run([]()->int {
        QThread::sleep(3);
        qDebug() << "sleeped 3s";
        return 42;
    });
    qDebug() << "start concurrent";

    QFutureWatcher<int> watcher;
    watcher.setFuture(future);
    auto b = new QtCoroutine([&watcher](const QtYield & yield)->void {
        yield(&watcher, SIGNAL(finished()));
        qDebug() << "result" << watcher.result();
    });
    // NOTE when coroutine finished (i.e. reaches end or return), `finished()` emitted
    b->connect(b, SIGNAL(finished()), SLOT(deleteLater()));
    a.connect(b, SIGNAL(finished()), SLOT(quit()));
    b->start();

    return a.exec();
}

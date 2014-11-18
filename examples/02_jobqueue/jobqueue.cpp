#include <QtCore/QtDebug>

#include "jobqueue.hpp"

JobQueue::JobQueue ():
_currentCallback(nullptr) {
}

QtCoroutine * JobQueue::setTimeout (int msIntevel, QtCoroutine::Callback callback) {
    auto job = new QtCoroutine([=](const QtYield & yield)->void {
        yield(msIntevel);

        this->_enqueue(callback);
        this->_dequeue();
    });
    job->start();
    return job;
}

void JobQueue::_enqueue (QtCoroutine::Callback callback) {
    this->_queue.push(callback);
}

void JobQueue::_dequeue () {
    if (this->_queue.empty()) {
        qDebug() << "no callback remain, stop chaining";
        return;
    }
    if (this->_currentCallback) {
        qDebug() << "a callback arrived but queued";
        return;
    }

    this->_currentCallback = this->_queue.front();
    this->_queue.pop();
    auto callback = new QtCoroutine(this->_currentCallback);
    callback->connect(callback, SIGNAL(finished()), SLOT(deleteLater()));
    this->connect(callback, SIGNAL(finished()), SLOT(_reset()));
    this->connect(callback, SIGNAL(finished()), SLOT(_dequeue()));
    callback->start();
}

void JobQueue::_reset () {
    this->_currentCallback = nullptr;
}

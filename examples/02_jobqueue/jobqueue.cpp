#include <QtCore/QtDebug>

#include "jobqueue.hpp"


JobQueue::JobQueue ()
    : _currentCallback(nullptr)
{
}


qtael::Async * JobQueue::setTimeout (int msIntevel, qtael::Function callback) {
    auto job = new qtael::Async([=](const qtael::Await & await)->void {
        await(msIntevel);

        this->_enqueue(callback);
        this->_dequeue();
    });
    job->start();
    return job;
}


void JobQueue::_enqueue (qtael::Function callback) {
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
    auto callback = new qtael::Async(this->_currentCallback);
    callback->connect(callback, SIGNAL(finished()), SLOT(deleteLater()));
    this->connect(callback, SIGNAL(finished()), SLOT(_reset()));
    this->connect(callback, SIGNAL(finished()), SLOT(_dequeue()));
    callback->start();
}


void JobQueue::_reset () {
    this->_currentCallback = nullptr;
}

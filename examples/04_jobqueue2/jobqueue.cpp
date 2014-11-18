#include <QtCore/QtDebug>

#include "jobqueue.hpp"

JobQueue::JobQueue ():
_nextHandle(0LL),
_queue(),
_currentCallback(nullptr) {
}

qint64 JobQueue::setTimeout (int msIntevel, QtCoroutine::Callback callback) {
    auto cb = new QtCoroutine(callback);
    cb->connect(cb, SIGNAL(finished()), SLOT(deleteLater()));
    auto job = new QtCoroutine([this, msIntevel, cb](const QtYield & yield)->void {
        yield(msIntevel);

        this->_enqueue(cb);
        this->_dequeue();
    });
    this->_handles.insert(std::make_pair(this->_nextHandle, std::make_tuple(job, cb)));
    job->start();
    return this->_nextHandle++;
}

void JobQueue::clear (qint64 handle) {
    auto it = this->_handles.find(handle);
    if (it == this->_handles.end()) {
        return;
    }
    auto handler = it->second;
    auto job = std::get<0>(handler);
    job->stop();
    job->deleteLater();
    auto callback = std::get<1>(handler);
    auto it2 = std::remove(this->_queue.begin(), this->_queue.end(), callback);
    this->_queue.erase(it2);
    if (this->_currentCallback == callback) {
        callback->stop();
    }
    callback->deleteLater();
}

void JobQueue::_enqueue (QtCoroutine * callback) {
    this->_queue.push_back(callback);
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
    this->_queue.pop_front();
    auto runner = new QtCoroutine([this](const QtYield & yield)->void {
        this->_currentCallback->start();

        yield(this->_currentCallback, SIGNAL(finished()));
        this->_currentCallback = nullptr;
        this->_dequeue();
    });
    runner->start();
}

void JobQueue::_reset () {
    this->_currentCallback = nullptr;
}

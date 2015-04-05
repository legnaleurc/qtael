#include "qtcoroutine.hpp"
#include "qtcoroutine_p.hpp"

#include <QtCore/QTimer>

#include <cassert>

QtCoroutine::QtCoroutine (Callback task, QObject *parent): QObject(parent),
d(new Private(task, this)) {
    this->connect(this->d, SIGNAL(finished()), SIGNAL(finished()));
}

void QtCoroutine::start () {
    this->d->fork = Private::Coroutine::call_type([&](Private::Coroutine::yield_type & yield)->void {
        QtYield yield_(std::make_shared<QtYield::Private>(*this, yield));
        this->d->task(yield_);
    });
    this->d->tail();
}

void QtCoroutine::stop () {
    // remove signal isolator
}

QtYield::QtYield (std::shared_ptr<Private> d):
d(d) {
}

QtYield::~QtYield () {
}

void QtYield::operator () (int interval) const {
    QTimer::singleShot(interval, this->d->task.d, SLOT(postAction()));
    this->d->yield();
}

void QtYield::operator () (QObject * object, const char * signal_) const {
    SignalIsolator si;
    si.connect(object, signal_, SIGNAL(proxy()));
    this->d->task.d->connect(&si, SIGNAL(proxy()), SLOT(postAction()));
    this->d->yield();
}

QtCoroutine::Private::Private (Callback task, QObject *parent): QObject(parent),
task(task),
fork() {
}

void QtCoroutine::Private::tail () {
    if (!this->fork) {
        emit this->finished();
    }
}

void QtCoroutine::Private::postAction () {
    assert(this->fork || !"coroutine error");
    this->fork();
    this->tail();
}

QtYield::Private::Private(QtCoroutine & task, Coroutine::yield_type & yield) :
task(task),
yield(yield) {
}

#ifndef QTCOROUTINE_HPP_
#define QTCOROUTINE_HPP_

#include "qtcoroutine.hpp"

#include <boost/coroutine/stack_allocator.hpp>
#include <boost/coroutine/coroutine.hpp>

class QtCoroutine::Private: public QObject {
    Q_OBJECT
public:
    typedef boost::coroutines::symmetric_coroutine<void> Coroutine;

    Private (QtCoroutine::Callback task, QObject * parent);

    void tail ();

signals:
    void finished ();

public slots:
    void postAction ();

public:
    QtCoroutine::Callback task;
    Coroutine::call_type fork;
};

class QtYield::Private {
public:
    typedef QtCoroutine::Private::Coroutine Coroutine;

    Private(QtCoroutine & task, Coroutine::yield_type & yield);

    QtCoroutine & task;
    Coroutine::yield_type & yield;
};

class SignalIsolator : public QObject {
    Q_OBJECT
signals:
    void proxy();
};

#endif

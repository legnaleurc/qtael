#ifndef QTCOROUTINE_HPP_
#define QTCOROUTINE_HPP_

#include "qtcoroutine.hpp"

// #include <boost/coroutine/stack_allocator.hpp>
#include <boost/coroutine2/coroutine.hpp>

class QtCoroutine::Private: public QObject {
    Q_OBJECT
public:
    typedef boost::coroutines2::coroutine<void> Coroutine;

    Private (QtCoroutine::Callback task, QObject * parent);

    void tail ();

signals:
    void finished ();

public slots:
    void postAction ();

public:
    QtCoroutine::Callback task;
    Coroutine::pull_type fork;
};

class QtYield::Private {
public:
    typedef QtCoroutine::Private::Coroutine Coroutine;

    Private(QtCoroutine & task, Coroutine::push_type & yield);

    QtCoroutine & task;
    Coroutine::push_type & yield;
};

class SignalIsolator : public QObject {
    Q_OBJECT
signals:
    void proxy();
};

#endif

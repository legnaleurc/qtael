#ifndef QTAEL_HPP_
#define QTAEL_HPP_

#include "qtael.hpp"

#include <boost/coroutine2/coroutine.hpp>


namespace qtael {

class Async::Private: public QObject {
    Q_OBJECT
public:
    typedef boost::coroutines2::coroutine<void> Coroutine;

    Private (Function task, QObject * parent);

    void tail ();

signals:
    void finished ();

public slots:
    void postAction ();

public:
    Function task;
    Coroutine::pull_type fork;
};

class Await::Private {
public:
    typedef Async::Private::Coroutine Coroutine;

    Private (Async & context, Coroutine::push_type & yield);

    Async & context;
    Coroutine::push_type & yield;
};

}

#endif

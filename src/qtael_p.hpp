#ifndef QTAEL_HPP_
#define QTAEL_HPP_

#include "qtael.hpp"

#include <boost/coroutine2/coroutine.hpp>


namespace qtael {

using Coroutine = boost::coroutines2::coroutine<void>;
using Receiver = Coroutine::pull_type;
using Sender = Coroutine::push_type;


class Async::Private : public QObject {
    Q_OBJECT
public:
    Private (Function task, QObject * parent);

signals:
    void finished ();

public slots:
    void onResolve ();

public:
    Function task;
    Receiver fork;
};


class Await::Private {
public:
    Private (Async & context, Sender & yield);

    Async & context;
    Sender & yield;
};

}

#endif

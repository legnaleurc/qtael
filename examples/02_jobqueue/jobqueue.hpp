#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <queue>

#include <QtCore/QObject>

#include "qtcoroutine.hpp"

class JobQueue: public QObject {
    Q_OBJECT
public:
    JobQueue ();

    QtCoroutine * setTimeout (int msIntevel, QtCoroutine::Callback callback);

private slots:
    void _dequeue ();
    void _reset ();

private:
    void _enqueue (QtCoroutine::Callback callback);

    std::queue<QtCoroutine::Callback> _queue;
    QtCoroutine::Callback _currentCallback;
};

#endif

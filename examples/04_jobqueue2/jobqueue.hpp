#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <deque>
#include <unordered_map>

#include <QtCore/QObject>

#include "qtcoroutine.hpp"

class JobQueue: public QObject {
    Q_OBJECT
public:
    JobQueue ();

    qint64 setTimeout (int msIntevel, QtCoroutine::Callback callback);

    void clear(qint64 handle);

private slots:
    void _dequeue ();
    void _reset ();

private:
    void _enqueue (QtCoroutine * callback);

    qint64 _nextHandle;
    typedef std::unordered_map<qint64, std::tuple<QtCoroutine *, QtCoroutine *>> HandleTable;
    HandleTable _handles;
    std::deque<QtCoroutine *> _queue;
    QtCoroutine * _currentCallback;
};

#endif

#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <deque>
#include <unordered_map>

#include <QtCore/QObject>

#include "qtael.hpp"


class JobQueue: public QObject {
    Q_OBJECT
public:
    JobQueue ();

    qint64 setTimeout (int msIntevel, qtael::Function callback);

    void clear(qint64 handle);

private slots:
    void _dequeue ();
    void _reset ();

private:
    void _enqueue (qtael::Async * callback);

    qint64 _nextHandle;
    typedef std::unordered_map<qint64, std::tuple<qtael::Async *, qtael::Async *>> HandleTable;
    HandleTable _handles;
    std::deque<qtael::Async *> _queue;
    qtael::Async * _currentCallback;
};

#endif

#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <queue>

#include <QtCore/QObject>

#include "qtael.hpp"


class JobQueue: public QObject {
    Q_OBJECT
public:
    JobQueue ();

    qtael::Async * setTimeout (int msIntevel, qtael::Function callback);

private slots:
    void _dequeue ();
    void _reset ();

private:
    void _enqueue (qtael::Function callback);

    std::queue<qtael::Function> _queue;
    qtael::Function _currentCallback;
};

#endif

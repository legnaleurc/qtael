#include "qtael_p.hpp"

#include <cassert>

#include <QtCore/QTimer>


using namespace qtael;


Async::Async (Function task, QObject * parent)
    : QObject(parent)
    , d(new Private(task, this))
{
    this->connect(this->d, SIGNAL(finished()), SIGNAL(finished()));
}


void Async::start () {
    this->d->fork = Receiver{[&](Sender & yield) -> void {
        Await await(std::make_shared<Await::Private>(*this, yield));
        this->d->task(await);
    }};
}


void Async::stop () {
    assert(!"not supported yet");
}


Await::Await (std::shared_ptr<Private> d)
    : d(d)
{
}


Await::~Await () {
}


void Await::operator () (int interval) const {
    QTimer::singleShot(interval, this->d->context.d, SLOT(postAction()));
    this->d->yield();
}


void Await::yield (QObject * object) const {
    this->d->context.d->connect(object, SIGNAL(resolved()), SLOT(postAction()));
    this->d->yield();
}


Async::Private::Private (Function task, QObject *parent)
    : QObject(parent)
    , task(task)
    , fork([](Sender &) -> void {})
{
}

void Async::Private::tail () {
    if (!this->fork) {
        emit this->finished();
    }
}

void Async::Private::postAction () {
    this->fork();
    this->tail();
}

Await::Private::Private (Async & context, Sender & yield)
    : context(context)
    , yield(yield)
{
}

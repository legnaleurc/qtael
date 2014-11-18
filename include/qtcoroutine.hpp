#ifndef QTCOROUTINE_HPP
#define QTCOROUTINE_HPP

#include <QtCore/QObject>

#include <functional>
#include <memory>

#ifdef QTCOROUTINE_LIBRARY
#define QTCOROUTINE_DLL Q_DECL_EXPORT
#else
#define QTCOROUTINE_DLL Q_DECL_IMPORT
#endif

class QtYield;

class QTCOROUTINE_DLL QtCoroutine : public QObject {
    Q_OBJECT
public:
    typedef std::function<void (const QtYield &)> Callback;

    explicit QtCoroutine (Callback task, QObject * parent = 0);

    void start ();
    void stop ();

signals:
    void finished ();

private:
    friend class QtYield;
    class Private;
    Private * d;
};

class QTCOROUTINE_DLL QtYield {
public:
    void operator () (int interval) const;
    void operator () (QObject * object, const char * signal_) const;

private:
    friend class QtCoroutine;
    class Private;

    QtYield (std::shared_ptr<Private> d);
    QtYield (const QtYield &);
    QtYield & operator = (const QtYield &);
    QtYield (QtYield &&);
    QtYield & operator = (QtYield &&);
    ~QtYield();

    std::shared_ptr<Private> d;
};

#endif

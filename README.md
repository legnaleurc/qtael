# QtCoroutine

This library integrates [Boost.Coroutine] into [Qt].

You can **yield** in an event loop, instead of creating `QEventLoop` to wait
something done.

## Example

```cpp
auto task = new QtCoroutine([](const QtYield & yield)->void {
    QNetworkAccessManager nasm;
    QUrl url("https://www.google.com/");
    QNetworkRequest request(url);

    auto reply = nasm.get(request);
    // NOTE yield to main event loop until request finished
    yield(reply, SIGNAL(finished()));

    auto data = reply->readAll();
    reply->deleteLater();

    qDebug() << data;
});

// NOTE when coroutine finished (i.e. reaches end or return), `finished()` emitted
task->connect(task, SIGNAL(finished()), SLOT(deleteLater()));
// NOTE start this task, will not block event loop
task->start();
```

## Build Dependency

* [CMake] >= 2.8
* [Qt] => 5.0
* [Boost.Coroutine] >= 1.56
* C++11 supported toolchain

## How to Build

```
mkdir build
cd build
cmake ..
make
```

## How to Install

```
make install
```


[Boost.Coroutine]: http://www.boost.org/
[CMake]: http://www.cmake.org/
[Qt]: http://qt-project.org/

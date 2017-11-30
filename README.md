# Qt Asynchronous Event Loop

This library integrates [Boost.Coroutine2] into [Qt].

You can **await** in an event loop, instead of creating `QEventLoop` to wait
something done.

## Example

```cpp
auto task = new qtael::Async([](const qtael::Await & await) -> void {
    QNetworkAccessManager nasm;
    QUrl url{"https://www.google.com/"};
    QNetworkRequest request{url};

    auto reply = nasm.get(request);
    // NOTE yield to main event loop until the request finished
    await(reply, &QNetworkReply::finished);

    auto data = reply->readAll();
    reply->deleteLater();

    qDebug() << data;
});

// NOTE When the asynchronous function finished (i.e. reaches end or return),
// signal `finished()` will be emitted.
task->connect(task, SIGNAL(finished()), SLOT(deleteLater()));
// NOTE start this task, and it will not block the event loop
task->start();
```

## Build Dependency

* [CMake] >= 3.8
* [Qt] => 5.6
* [Boost.Coroutine2] >= 1.59
* C++14 supported toolchain

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


[Boost.Coroutine2]: https://github.com/boostorg/coroutine2
[CMake]: https://cmake.org/
[Qt]: https://www.qt.io/

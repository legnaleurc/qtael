#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>

class HttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = 0);

    bool listen(quint16 port);

signals:

public slots:

private slots:
    void _onNewConnection();
    void _onClientReadyRead();
    void _onClientDisconnected();

private:
    QTcpServer * _server;
};

#endif // HTTPSERVER_H

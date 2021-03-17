#ifndef RCON_H
#define RCON_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QTcpSocket>

#define LISTEN_PORT 8999

class RconServer : public QObject
{
    Q_OBJECT

public:
    explicit RconServer(QObject *parent = nullptr);
    ~RconServer();

    void run();

private:
    QTcpServer *server;
    QList<QTcpSocket*> sockets;

private slots:
    void newConnection();
    void readyRead();
};

#endif // RCON_H

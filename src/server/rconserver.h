#ifndef RCON_H
#define RCON_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QTcpSocket>

#include "fc2dedicatedserver.h"

#define LISTEN_PORT 8999

class RconServer : public QObject
{
    Q_OBJECT

public:
    explicit RconServer(QObject *parent = nullptr);
    ~RconServer();

    void run();

private:
    enum MessageType {
        AUTHENTICATION,
        ACTION,
        COMMAND,
        RESPONSE
    };

    enum Action {
        LAUNCH,
        STOP
    };

    QTcpServer *server = nullptr;
    QList<QTcpSocket*> sockets;

    FC2DedicatedServer *fc2 = nullptr;

private slots:
    void newConnection();
    void readyRead();
    void write(const QByteArray &data);
};

#endif // RCON_H

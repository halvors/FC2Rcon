#include <QDebug>
#include <QString>

#include "rconserver.h"
#include "packet.h"

RconServer::RconServer(QObject *parent) : QObject(parent)
{

}

RconServer::~RconServer()
{

}

void RconServer::run()
{
    if (!server) {
        server = new QTcpServer(this);

        connect(server, &QTcpServer::newConnection, this, &RconServer::newConnection);
    }

    if (!server->isListening()) {
        server->listen(QHostAddress::Any, LISTEN_PORT);

        qDebug().noquote() << QString("Server listening on port %1").arg(server->serverPort());
    }

    if (!fc2) {
        fc2 = new FC2DedicatedServer(this);
        connect(fc2, &FC2DedicatedServer::commandResult, this, &RconServer::write);
    }

    fc2->start();
}

void RconServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QAbstractSocket::readyRead, this, &RconServer::readyRead);
    sockets.push_back(socket);

    socket->write("Welcome to FC2Rcon!");

    qDebug().noquote() << QString("New connection from %1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
}

void RconServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(QObject::sender());

    while (socket->bytesAvailable() > 0) {
        QDataStream in(socket);
        Packet packet;
        in >> packet;

        QByteArray data = packet.data;

        if (!data.isEmpty()) {
            QString command = QString::fromUtf8(data);

            qDebug().noquote() << QString("Received: %1").arg(command);
            fc2->sendCommand(command);
        }
    }
}

void RconServer::write(const QByteArray &data)
{
    for (QTcpSocket *socket : sockets) {
        QDataStream out(socket);
        Packet packet(Packet::Origin::Server, Packet::Type::Response, data);
        out << packet;
    }
}

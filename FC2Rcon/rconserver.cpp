#include "rconserver.h"

#include <QDebug>

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
        server->listen(QHostAddress::AnyIPv4, LISTEN_PORT);

        qDebug().noquote() << QString("Server listening on port %1").arg(server->serverPort());
    }
}

void RconServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QAbstractSocket::readyRead, this, &RconServer::readyRead);
    sockets.push_back(socket);

    qDebug().noquote() << QString("New connection from %1:%2").arg(socket->peerAddress().toIPv4Address()).arg(socket->peerPort());
}

void RconServer::readyRead()
{

}

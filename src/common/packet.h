#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QDataStream>

class Packet
{
public:
    enum Origin {
        Server,
        Client
    };

    enum Type {
        Auth,
        Request,
        Response
    };

    Packet();
    Packet(enum Origin origin, enum Type type, const QByteArray &data);
    ~Packet();

    uint32_t length = 0;
    enum Origin origin;
    enum Type type;
    QByteArray data;

    void calculateLength();
    void clear();
};

QDataStream &operator <<(QDataStream &out, const Packet &packet);
QDataStream &operator >>(QDataStream &in, Packet &packet);

#endif // PACKET_H

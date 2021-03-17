#include "packet.h"

Packet::Packet()
{

}

Packet::Packet(enum Origin origin, enum Type type, const QByteArray &data) :
    origin(origin),
    type(type),
    data(data)
{
    calculateLength();
}

Packet::~Packet()
{
    clear();
}

void Packet::clear()
{
    length = 0;
    data.clear();
}

void Packet::calculateLength()
{
    if (length == 0)
        length = sizeof(origin) + sizeof(type) + data.length();
}

QDataStream &operator <<(QDataStream &out, const Packet &packet)
{
    out << packet.length;
    out << packet.origin;
    out << packet.type;
    out << packet.data;

    return out;
}

QDataStream &operator >>(QDataStream &in, Packet &packet)
{
    packet.clear();

    in >> packet.length;

    uint32_t origin;
    in >> origin;
    packet.origin = Packet::Origin(origin);

    uint32_t type;
    in >> type;
    packet.type = Packet::Type(type);

    // TODO: make sure to read right length here?
    in >> packet.data;

    return in;
}

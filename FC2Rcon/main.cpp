#include <QCoreApplication>

#include "rcon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    rcon rcon;

    return a.exec();
}

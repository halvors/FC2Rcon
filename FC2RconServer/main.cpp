#include <QCoreApplication>

#include "rconserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RconServer rconServer;
    rconServer.run();

    return a.exec();
}

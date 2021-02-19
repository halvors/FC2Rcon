#include "rcon.h"

#include <QCoreApplication>
#include <QDebug>

rcon::rcon(QObject *parent) : QObject(parent)
{
    proc = new QProcess(this);
    proc->setWorkingDirectory("/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin");
    proc->setProgram("wine");
    proc->setArguments(QStringList() << "FC2ServerLauncher.exe" << "-borderless" << "-noredirectstdin");
    proc->setProcessChannelMode(QProcess::SeparateChannels);
    proc->setReadChannel(QProcess::ProcessChannel::StandardOutput);

    connect(proc, &QProcess::readyReadStandardOutput, this, &rcon::readyReadStandardOutput);
    connect(proc, &QProcess::readyReadStandardError, this, &rcon::readyReadStandardError);
    connect(proc, &QProcess::readyRead, this, &rcon::readyRead);

    // Start the process
    proc->start();
    QCoreApplication::processEvents();
    proc->waitForStarted();

    // Read the output
    proc->waitForReadyRead();
    //QString output(proc->readAllStandardOutput());

    // Write the data
    sendCommand("net_GetCurrentMapName");            // Displays the current map name.
    sendCommand("net_GetCurrentGameModeName");     // Displays the current game mode name.
    sendCommand("net_GetHostAddress");             // Displays the host address.
    sendCommand("net_GetHostName");                // Displays the host name.
    sendCommand("net_GetCurrentSessionMaxPlayer"); // Displays the maximum number of players for the current session.
    sendCommand("net_GetPlayerList");              // Get the player list.
    sendCommand("net_GetPlayerListByTeam");        // Get the player list by team.
    sendCommand("net_GetCaptainNames");            // Get the name of each captain.
    sendCommand("net_GetGameScoreStats");          // Get the current game score statistics.
    //proc->closeWriteChannel();

    proc->waitForReadyRead();
    qDebug() << proc->readAll();

    // Wait for finished
    proc->waitForFinished();
}

void rcon::sendCommand(const QString &cmd)
{
    proc->write(cmd.toUtf8().append('\n'));
    proc->waitForBytesWritten();
}

void rcon::readyReadStandardOutput()
{
    qDebug() << "Got stdout!";
}

void rcon::readyReadStandardError()
{
    //qDebug() << "Got stderr!";
    //qDebug() << proc->readAllStandardError();
}

void rcon::readyRead()
{
    qDebug() << proc->readAll();
}

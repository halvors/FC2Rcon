#include "rcon.h"

#include <QCoreApplication>
#include <QDebug>

#include <QDir>
#include <QProcess>

rcon::rcon(QObject *parent) : QObject(parent)
{
    const QString workDir = "/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin";
    const QString execFile = "FC2ServerLauncher.exe";

    proc = new QProcess(this);
    proc->setWorkingDirectory(workDir);
    proc->setProgram("wine");
    proc->setArguments(QStringList() << execFile << "-noredirectstdin");
    proc->setProcessChannelMode(QProcess::SeparateChannels);

    proc->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args)
        {
            args->flags |= CREATE_NEW_CONSOLE;
            args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
            args->startupInfo->dwFlags |= STARTF_USEFILLATTRIBUTE;
            args->startupInfo->dwFillAttribute = BACKGROUND_BLUE | FOREGROUND_RED
                                               | FOREGROUND_INTENSITY;
        });

    connect(proc, &QProcess::readyReadStandardOutput, this, &rcon::readyReadStandardOutput);
    connect(proc, &QProcess::readyReadStandardError, this, &rcon::readyReadStandardError);
    connect(proc, &QProcess::readyRead, this, &rcon::readyRead);

    //QString qsExePath = "C:\\Program Files (x86)\\Some Company\\SomeApp.exe";
    bool bStarted = proc->startDetached("wine /mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin/FC2ServerLauncher.exe", QStringList());

    // Start the process
    //proc->start();
    //QCoreApplication::processEvents();
    proc->waitForStarted();

    qDebug() << "Process started";

    // Read the output
    proc->waitForReadyRead();

    qDebug() << "Ready to write";

    // Write the data
    //sendCommand("net_GetCurrentMapName");          // Displays the current map name.
    //sendCommand("net_GetCurrentGameModeName");     // Displays the current game mode name.
    sendCommand("net_GetHostAddress");             // Displays the host address.
    //sendCommand("net_GetHostName");                // Displays the host name.
    //sendCommand("net_GetCurrentSessionMaxPlayer"); // Displays the maximum number of players for the current session.
    //sendCommand("net_GetPlayerList");              // Get the player list.
    //sendCommand("net_GetPlayerListByTeam");        // Get the player list by team.
    //sendCommand("net_GetCaptainNames");            // Get the name of each captain.
    //sendCommand("net_GetGameScoreStats");          // Get the current game score statistics.
    //proc->closeWriteChannel();

    //proc->waitForReadyRead();
    //qDebug() << proc->readAll();

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
    qDebug() << proc->readAllStandardOutput();
}

void rcon::readyReadStandardError()
{
    qDebug() << "Got stderr!";
    qDebug() << proc->readAllStandardError();
}

void rcon::readyRead()
{
    qDebug() << proc->readAll();
}

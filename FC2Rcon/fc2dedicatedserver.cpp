#include "fc2dedicatedserver.h"

#include <QDebug>

#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

FC2DedicatedServer::FC2DedicatedServer(QObject *parent) : QObject(parent)
{
    QString path;
    const QString execFile = "FC2ServerLauncher.exe";
    QStringList args = QStringList() << "-noredirectstdin";

#if defined(Q_OS_WIN)
    path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Far Cry 2\\bin";
#elif defined(Q_OS_LINUX)
    path = "/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin";
    args.prepend("wine");
#endif

    proc = new QProcess(this);
    proc->setWorkingDirectory(path);
    proc->setProgram(QString("%1/%2").arg(path).arg(execFile));
    proc->setArguments(args);
    proc->setProcessChannelMode(QProcess::SeparateChannels);

#if defined(Q_OS_WIN)
    proc->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args)
    {
        STARTUPINFO *si = args->startupInfo;
        si->dwFlags |= STARTF_USESHOWWINDOW;
        //si->wShowWindow = SW_HIDE;
    });
#endif

    connect(proc, &QProcess::readyRead, this, &FC2DedicatedServer::readyRead);
    connect(proc, &QProcess::errorOccurred, this, &FC2DedicatedServer::errorOccurred);
    //connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus){ startFC2ServerInstance(); });

    if (startFC2ServerInstance())
        qDebug() << "Started process!";
    else
        qDebug() << "Process did not start!";
}

FC2DedicatedServer::~FC2DedicatedServer()
{
    proc->kill();
}

bool FC2DedicatedServer::startFC2ServerInstance()
{
    // Start the process
    proc->start();

    return proc->waitForStarted();
}

void FC2DedicatedServer::sendCommand(const QString &cmd)
{
    proc->write(cmd.toUtf8().append('\n'));
    proc->waitForBytesWritten();
}

void FC2DedicatedServer::errorOccurred(QProcess::ProcessError error)
{
    qDebug() << "Error:" << error;
}

void FC2DedicatedServer::readyRead()
{
    while (proc->bytesAvailable() && proc->canReadLine()) {
        QByteArray line = proc->readLine();

        if (line.contains("Entering lobby!")) {
            readyForInput = true;
            sendCommand("net_GetHostAddress");
        }

        if (readyForInput)
            qDebug() << line;
    }
}

//sendCommand("net_GetCurrentMapName");          // Displays the current map name.
//sendCommand("net_GetCurrentGameModeName");     // Displays the current game mode name.
//sendCommand("net_GetHostAddress");             // Displays the host address.
//sendCommand("net_GetHostName");                // Displays the host name.
//sendCommand("net_GetCurrentSessionMaxPlayer"); // Displays the maximum number of players for the current session.
//sendCommand("net_GetPlayerList");              // Get the player list.
//sendCommand("net_GetPlayerListByTeam");        // Get the player list by team.
//sendCommand("net_GetCaptainNames");            // Get the name of each captain.
//sendCommand("net_GetGameScoreStats");          // Get the current game score statistics.

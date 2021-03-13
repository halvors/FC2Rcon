#include "rcon.h"

#include <QCoreApplication>
#include <QDebug>

#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

rcon::rcon(QObject *parent) : QObject(parent)
{
#if defined(Q_OS_WIN)
    const QString path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Far Cry 2\\bin"; // "/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin"
#elif defined(Q_OS_LINUX)
    const QString path = "/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin";
#endif

    const QString execFile = "FC2ServerLauncher.exe";

    proc = new QProcess(this);
    proc->setWorkingDirectory(path);
    proc->setProgram(QString("%1/%2").arg(path).arg(execFile));
    proc->setArguments(QStringList() << "-noredirectstdin");
    proc->setProcessChannelMode(QProcess::SeparateChannels);

#if defined(Q_OS_WIN)
    proc->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args)
    {
        STARTUPINFO *si = args->startupInfo;
        si->dwFlags |= STARTF_USESHOWWINDOW;

        //si->wShowWindow = SW_HIDE;
        //args->flags |= CREATE_NEW_CONSOLE;
        //args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
        //args->startupInfo->dwFlags |= STARTF_USEFILLATTRIBUTE;
        // args->startupInfo->dwFillAttribute = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    });
#endif

    connect(proc, &QProcess::readyRead, this, &rcon::readyRead);
    connect(proc, &QProcess::errorOccurred, this, &rcon::errorOccurred);
    //connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus){ startFC2ServerInstance(); });

    /*
    if (startFC2ServerInstance())
        qDebug() << "Started process!";
    else
        qDebug() << "Process did not start!";
    */

    // Start the process
    proc->start();
    //QCoreApplication::processEvents();
    //proc->waitForStarted();

    /*
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
    */
}

rcon::~rcon()
{
    proc->kill();
}

bool rcon::startFC2ServerInstance()
{
    // Start the process
    proc->start();

    return proc->waitForStarted();
}

void rcon::sendCommand(const QString &cmd)
{
    proc->write(cmd.toUtf8().append('\n'));
    proc->waitForBytesWritten();
}

void rcon::errorOccurred(QProcess::ProcessError error)
{
    qDebug() << "Error:" << error;
}

void rcon::readyRead()
{
    while (proc->bytesAvailable() && proc->canReadLine()) {
        QByteArray line = proc->readLine();

        if (line.contains("Entering lobby!")) {
            readyForInput = true;
            sendCommand("net_GetHostAddress");
        }

        //if (readyForInput)
            qDebug() << line;
    }
}

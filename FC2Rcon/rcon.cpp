#include "rcon.h"

#include <QCoreApplication>
#include <QDebug>

#include <QDir>

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
    proc->setProgram(execFile);
    proc->setArguments(QStringList() << "-noredirectstdin");
    proc->setProcessChannelMode(QProcess::SeparateChannels);
    proc->setReadChannel(QProcess::ProcessChannel::StandardOutput);

    connect(proc, &QProcess::readyRead, this, &rcon::readyRead);
    //connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus){ startFC2ServerInstance(); });

    startFC2ServerInstance();

    // Start the process
    //proc->start();
    //QCoreApplication::processEvents();
    //proc->waitForStarted();

    /*
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

void rcon::readyRead()
{
    while (proc->bytesAvailable() && proc->canReadLine()) {
        QByteArray line = proc->readLine();

        if (line.contains("Entering lobby!")) {
            readyForInput = true;
            sendCommand("net_GetCurrentMapName");
        }

        if (readyForInput)
            qDebug() << line;
    }
}

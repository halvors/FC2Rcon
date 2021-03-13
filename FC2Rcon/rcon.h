#ifndef RCON_H
#define RCON_H

#include <QObject>
#include <QProcess>
#include <QString>

class rcon : public QObject
{
    Q_OBJECT

public:
    rcon(QObject *parent = nullptr);
    ~rcon();

private:
    QProcess *proc;
    bool readyForInput = false;

    void sendCommand(const QString &cmd);

private slots:
    bool startFC2ServerInstance();
    void errorOccurred(QProcess::ProcessError error);
    void readyRead();
};

#endif // RCON_H

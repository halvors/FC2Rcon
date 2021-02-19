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

private:
    QProcess *proc;

    void sendCommand(const QString &cmd);

private slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void readyRead();
};

#endif // RCON_H

#ifndef FC2DEDICATEDSERVER_H
#define FC2DEDICATEDSERVER_H

#include <QObject>
#include <QProcess>
#include <QString>

class FC2DedicatedServer : public QObject
{
    Q_OBJECT
public:
    explicit FC2DedicatedServer(QObject *parent = nullptr);
    ~FC2DedicatedServer();

    void sendCommand(const QString &cmd);

public slots:


private:
    QProcess *proc;
    bool readyForInput = false;

private slots:
    bool startFC2ServerInstance();
    void errorOccurred(QProcess::ProcessError error);
    void readyRead();
};

#endif // FC2DEDICATEDSERVER_H

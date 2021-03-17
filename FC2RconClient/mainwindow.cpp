#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QHostAddress>
#include <QAbstractSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::connected);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &MainWindow::displayError);
    connect(socket, &QAbstractSocket::readyRead, this, &MainWindow::readyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connected()
{
    qDebug().noquote() << QString("Connected to %1:%2").arg(socket->peerAddress().toIPv4Address()).arg(socket->peerPort());
}

void MainWindow::disconnected()
{
    qDebug().noquote() << "Disconnected.";
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;

    case QAbstractSocket::HostNotFoundError:
        qDebug().noquote() << "The host was not found. Please check the host name and port settings.";
        break;

    case QAbstractSocket::ConnectionRefusedError:
        qDebug().noquote() << "The connection was refused by the peer.";
        break;

    default:
        qDebug().noquote() << QString("The following error occurred: %1.").arg(socket->errorString());
    }
}

void MainWindow::readyRead()
{
    while (socket->bytesAvailable() > 0) {
        ui->textEdit->insertPlainText(socket->readLine());
    }
}

void MainWindow::on_pushButton_clicked()
{
    const QString host = "localhost";
    uint16_t port = 8999;

    socket->connectToHost(host, port);

    qDebug() << "lol";
}

void MainWindow::on_pushButton_2_clicked()
{
    QByteArray data = ui->lineEdit->text().toUtf8();

    if (!data.isEmpty())
        socket->write(data);
}

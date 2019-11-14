#include "sockettest.h"
#include "Collections.h"
SocketTest::SocketTest(QObject *parent) : QObject(parent)
{}

void SocketTest::Connect()
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    socket->connectToHost("wgforge-srv.wargaming.net", 443);
    if(socket->waitForConnected(500))
    {
        qDebug() << "Connected!";
    }
    else
    {
        qDebug() << "Not connected!";
    }
}

void SocketTest::SendMessage(Actions Action, QJsonObject jsonObj)
{
    QByteArray jsonData;
    jsonData = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
    QByteArray content("\x01\x00\x00\x00\x10\x00\x00\x00", 8);
    if(socket->isOpen())
    {
        socket->write(content + jsonData);
        qDebug() << content + jsonData;
        socket->waitForBytesWritten(500);
    } else {
        qDebug() << "socket is close";
    }
    socket->readyRead();
}


void SocketTest::readyRead()
{
    if(socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug() << Data;
        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.errorString().toInt() == QJsonParseError::NoError)
        {
        }
    }
}


void SocketTest::disconnect()
{
    socket->deleteLater();
}

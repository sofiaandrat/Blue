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
    if(socket->isOpen())
    {
        socket->write(toMessageFormat(Action,jsonObj));
        qDebug()<< toMessageFormat(Action,jsonObj);
    } else {
        qDebug() << "socket is close";
    }
    socket->readyRead();

}


void SocketTest::readyRead()
{
    if(socket->waitForConnected(500))
    {
        if(socket->waitForReadyRead(500))
        {
            Data = socket->readAll();
            qDebug() << Data;
            this->doc = QJsonDocument::fromJson(Data);
            if(this->doc.isEmpty())
                qDebug() << "blaaa";
            Data.clear();
        }
    }
}


void SocketTest::disconnect()
{
    socket->deleteLater();
}

QByteArray SocketTest::toMessageFormat(Actions Action,QJsonObject jsonObj) {

    QByteArray jsonData = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);

    int int_action = Action;
    int* action = &int_action;
    int int_jsonSize = jsonData.size();
    int* jsonSize = &int_jsonSize;

    QByteArray bytes_action((char*)action,4);
    QByteArray bytes_jsonSize((char*)jsonSize,4);

    return bytes_action + bytes_jsonSize + jsonData;
}

QJsonDocument SocketTest::getterDoc()
{
    return this->doc;
}

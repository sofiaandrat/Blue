#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include "Collections.h"
class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = nullptr);
    void Connect();
    void SendMessage(Actions Action, QJsonObject jsonData);
    void SendMessage1(Actions Action, QJsonObject jsonData);
signals:

public slots:
    void readyRead();
    void disconnect();
private:
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    QByteArray toMessageFormat(Actions Action,QJsonObject jsonObj);
};

#endif // SOCKETTEST_H

#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include "Model/isocketservice.h"

class SocketService :public ISocketService
{
public:
    SocketService();
    void OpenConnection() override;
    void SendMessage(Actions Action, QJsonObject jsonObj) override;
    QVector<game> GetGames() override;
private:
    SocketTest *socket;
};

#endif // SOCKETSERVICE_H

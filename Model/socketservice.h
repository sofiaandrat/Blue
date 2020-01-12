#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include "sockettest.h"
#include "isocketservice.h"

class SocketService : public ISocketService
{
public:
    SocketService();
    ~SocketService() override;
    void OpenConnection() override;
    QVector<game> GetGames() override;
    void SendMessage(Actions Action, QJsonObject jsonObj) override;
private:
    SocketTest *socket;

};

#endif // SOCKETSERVICE_H

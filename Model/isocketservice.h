#ifndef ISOCKETSERVICE_H
#define ISOCKETSERVICE_H

#include "Model/structs.h"

class ISocketService
{
public:
    virtual ~ISocketService(){}
    virtual void OpenConnection() = 0;
    virtual QVector <game> GetGames() = 0;
    virtual void SendMessage(Actions Action, QJsonObject jsonObj) = 0;
};

#endif // ISOCKETSERVICE_H

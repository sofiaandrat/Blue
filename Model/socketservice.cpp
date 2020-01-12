#include "socketservice.h"

SocketService::SocketService()
{
    socket = new SocketTest();
}

SocketService::~SocketService()
{

}

void SocketService::OpenConnection()
{
    socket->Connect();
}

QVector <game> SocketService::GetGames()
{
    socket->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(socket->getterDoc());
    QVector <game> gameList = games.getGames();
    return gameList;
}

void SocketService::SendMessage(Actions Action, QJsonObject jsonObj)
{
    socket->SendMessage(Action, jsonObj);
}

#ifndef STRATEGY_H
#define STRATEGY_H
#include <QVector>
#include "structs.h"
#include "dijkstrasalg.h"
#include "sockettest.h"
class Strategy //бедный SOLID громко плачет
{
private:
    QVector <QVector <int> > shortestPaths;
    QVector<int> pointsOfGraph;
    DijkstrasAlg alg;
    SocketTest *socket;
    int indexOfFirstArmorTrain = 0;
    Map0 layer0;
public:
    Strategy(int townIdx,QVector <QVector <int> > &Table, QVector <int> pointsOfGraph, QVector<post> posts, SocketTest *socket, Map0 &layer0);
    market BestPost(Map1 map, QVector <market> posts, player Player, int pos);
    void Moving(Map1 &map, Player &player);
    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <market> GoodPosts(Map1 map, QVector <market> posts, Player player);
    void MakeRoute(Map1 map, Player &player, bool market, train Train);
    void NotCrashFunction(Player &player, train Train);
    void CreatePlanFunction(Map1 map, Player &player, train Train, QVector <market> posts);
    int CalculateLengthOfRoute(QVector <int> route);
    void Upgrade(Map1 &map, Player &player);
    void CalculateArmorTrain(Map1 &map, Player &player);
    void KillEnemy(Map1 &map, Player &player, train Train);
    void CalculateEnemy(Map1 map, train Train, bool isMarket, Player &player);
};

#endif // STRATEGY_H

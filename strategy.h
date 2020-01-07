#ifndef STRATEGY_H
#define STRATEGY_H
#include <QVector>
#include "structs.h"
#include "dijkstrasalg.h"
#include "sockettest.h"
class Strategy
{
private:
    QVector <QVector <int> > shortestPaths;
    QVector<int> pointsOfGraph;
    DijkstrasAlg alg;
    SocketTest *socket;
    int indexOfFirstArmorTrain = 0;
public:
    Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts, SocketTest *socket);
    market BestPost(Map1 map, QVector <market> posts, Player player, int pos);
    QVector <int> Moving(Map1 map, Player player, train currentTrain);
    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <market> GoodPosts(Map1 map, QVector <market> posts, Player player);
    void MakeRoute(Map1 map, Player player, bool market, train Train);
   // int NewStrategy(Map1 map, Player player, train currentTrain);
};

#endif // STRATEGY_H

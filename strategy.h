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
public:
    Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts, SocketTest *socket);
    market BestPost(Map1 map, QVector <market> posts, Player player);
    QVector <int> Moving(Map1 map, Player player);
    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <market> GoodPosts(Map1 map, QVector <market> posts, Player player);
};

#endif // STRATEGY_H

#ifndef STRATEGY_H
#define STRATEGY_H
#include <QVector>
#include "structs.h"
#include "dijkstrasalg.h"

class Strategy
{
private:
    QVector <QVector <int> > shortestPaths;
    QVector<int> pointsOfGraph;
    DijkstrasAlg alg;
public:
    Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph);
    QVector <int> Moving(Map1 map);
    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <int> BetterPath(Map1 map);
};

#endif // STRATEGY_H

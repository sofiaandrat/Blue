#ifndef DIJKSTRASALG_H
#define DIJKSTRASALG_H

#include <QVector>
#include <QDebug>
#include "structs.h"

class DijkstrasAlg
{
public:
    DijkstrasAlg(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph);

    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <int> Moving(Map1 map);
    QVector <QVector <int> > getPaths();
private:
    QVector <QVector <int> > shortestPaths;
    QVector <int> Path(bool fromTown, int pointIdx);
    int townIdx;
    QVector<int> pointsOfGraph;
};

#endif // DIJKSTRASALG_H

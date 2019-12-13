#ifndef DIJKSTRASALG_H
#define DIJKSTRASALG_H

#include <QVector>
#include <QDebug>
#include "structs.h"

class DijkstrasAlg
{
public:
    DijkstrasAlg(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph);

    QVector <int> Path(bool fromTown, int pointIdx);
    QVector <int> PathToNearestMarket(QVector<market> markets);
    QVector <QVector <int> > getPaths();
private:
    QVector <QVector <int> > shortestPaths;
    int townIdx;
    QVector<int> pointsOfGraph;
};

#endif // DIJKSTRASALG_H

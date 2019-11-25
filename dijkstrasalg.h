#ifndef DIJKSTRASALG_H
#define DIJKSTRASALG_H

#include <QVector>
#include <QDebug>

class DijkstrasAlg
{
public:
    DijkstrasAlg(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph);

    QVector <int> Path(bool fromTown, int pointIdx);
private:
    QVector <QVector <int> > shortestPaths;
    int townIdx;
};

#endif // DIJKSTRASALG_H

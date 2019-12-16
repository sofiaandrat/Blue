#ifndef DIJKSTRASALG_H
#define DIJKSTRASALG_H

#include <QVector>
#include <QDebug>
#include "structs.h"

class DijkstrasAlg
{
public:
    DijkstrasAlg(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts);

    QVector <QVector <int> > getPaths();
    QVector <QVector <int> > *shortestPaths;
    QVector <int> Path(bool fromTown, int pointIdx);
private:
    void shPathsFunc(int index, QVector<QVector<int> > &Table);
    QVector<post> mktAndStg;
    int townIdx;
    QVector<int> pointsOfGraph;
};

#endif // DIJKSTRASALG_H

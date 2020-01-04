#include "dijkstrasalg.h"
#include <iostream>
#include <QDebug>

DijkstrasAlg::DijkstrasAlg(int townIdx, QVector<QVector<int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts)
{
    this->townIdx = townIdx;
    this->pointsOfGraph = pointsOfGraph;
    this->mktAndStg = posts;
    for(int i = 0;i<mktAndStg.size();i++)
    {
        if(mktAndStg[i].type == 1){
            mktAndStg.remove(i);
            i--;
        }
    }
    //qDebug() << pointsOfGraph;
    this->shortestPaths = new QVector<QVector<int>>[mktAndStg.size()+1];
    shPathsFunc(0,Table);
    QVector<QVector<int>> tempTable = Table;
    int pSize = pointsOfGraph.size();
    int mSize = mktAndStg.size();
    for(int i = 0;i<mSize;i++)
    {
        int index = pointsOfGraph.indexOf(mktAndStg[i].point_idx);
        for(int k = 0;k<pSize;k++)
        {
            tempTable[index][k] = 0;
            tempTable[k][index] = 0;
        }
    }
    for(int i = 0;i<mSize;i++)
    {
        int index = pointsOfGraph.indexOf(mktAndStg[i].point_idx);
        for(int k = 0;k<pSize;k++)
        {
            tempTable[index][k] = Table[index][k];
            tempTable[k][index] = Table[k][index];
        }
        shPathsFunc(i+1,tempTable);
        for(int k = 0;k<pSize;k++)
        {
            tempTable[index][k] = 0;
            tempTable[k][index] = 0;
        }
    }
}

QVector<int> DijkstrasAlg::Path(bool fromTown, int pointIdx)
{
    QVector <int> path;
    path.append(pointsOfGraph.indexOf(pointIdx));
    if(fromTown)
    {
        bool flag = false;
        int idx;
        for(int i = 0;i<mktAndStg.size();i++) if(mktAndStg[i].point_idx == pointIdx)
        {
            flag = true;
            idx = i;
            break;
        }
        if(flag){
            for(int i = pointsOfGraph.indexOf(pointIdx);shortestPaths[idx+1][i][1]!=0;i = shortestPaths[idx+1][i][1])
            {
                path.append(shortestPaths[idx+1][i][1]);
            }
        }
        else
        {
            for(int i = pointsOfGraph.indexOf(pointIdx);shortestPaths[0][i][1]!=0;i = shortestPaths[0][i][1])
            {
                path.append(shortestPaths[0][i][1]);
            }
        }
       // path.append(0);
        std::reverse(path.begin(),path.end());
    }
    else
    {
        for(int i = pointsOfGraph.indexOf(pointIdx);shortestPaths[0][i][1]!=0;i = shortestPaths[0][i][1])
        {
            path.append(shortestPaths[0][i][1]);
        }
     //   path.append(0);
    }
    return path;
}

QVector <QVector <int> > DijkstrasAlg::getPaths() {
    return shortestPaths[0];
}

void DijkstrasAlg::shPathsFunc(int index, QVector<QVector<int> > &Table)
{
    int n = pointsOfGraph.size();
    QVector <QVector <int> > shortestPaths(n, QVector <int>(2, INT_MAX));
    QVector <bool> visited(n);
    for(int i=0;i<n;i++) {
        if(Table[townIdx][i]>0)
        {
            shortestPaths[i][0]=Table[townIdx][i];
            shortestPaths[i][1]=townIdx;
        }
        visited[i]=false;
    }

    shortestPaths[townIdx][0]=0;
    shortestPaths[townIdx][1]=0;
    int index1=0,u=0;
    for (int i=0;i<n;i++)
    {
        int min=INT_MAX;
        for (int j=0;j<n;j++)
        {
            if (!visited[j] && shortestPaths[j][0]<min)
            {
                min=shortestPaths[j][0];
                index1=j;
            }
        }
        u=index1;
        visited[u]=true;
        for(int j=0;j<n;j++)
        {
            if (!visited[j] && Table[u][j]!=0 && (shortestPaths[u][0]+Table[u][j]<shortestPaths[j][0]))
            {
                shortestPaths[j][0]=shortestPaths[u][0]+Table[u][j];
                shortestPaths[j][1]=u;
            }
        }
    }
    this->shortestPaths[index] = shortestPaths;
}

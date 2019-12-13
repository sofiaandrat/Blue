#include "dijkstrasalg.h"
#include <iostream>



DijkstrasAlg::DijkstrasAlg(int townIdx, QVector<QVector<int> > &Table, QVector<int> &pointsOfGraph)
{
    int n = pointsOfGraph.size();
    this->pointsOfGraph = pointsOfGraph;
    qDebug() << pointsOfGraph;
    QVector <QVector <int> > shortestPaths(n, QVector <int>(2, INT_MAX));
    bool visited[n];
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
    int index=0,u=0;
    for (int i=0;i<n;i++)
    {
        int min=INT_MAX;
        for (int j=0;j<n;j++)
        {
            if (!visited[j] && shortestPaths[j][0]<min)
            {
                min=shortestPaths[j][0];
                index=j;
            }
        }
        u=index;
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
    this->townIdx = townIdx;
    this->shortestPaths = shortestPaths;
    shortestPaths.clear();

}

QVector<int> DijkstrasAlg::Path(bool fromTown, int pointIdx)
{
    QVector <int> path;
    path.append(pointsOfGraph.indexOf(pointIdx));
    qDebug() << shortestPaths;
    qDebug() << path;
    for(int i = pointsOfGraph.indexOf(pointIdx);shortestPaths[i][1]!=0;i = shortestPaths[i][1])
    {
        path.append(shortestPaths[i][1]);
    }
    path.append(0);

    qDebug() << path;
    if(fromTown)
    {
        std::reverse(path.begin(),path.end());
    }
    return path;
}

QVector<int>  DijkstrasAlg::PathToNearestMarket(QVector<market> markets){
    int min_route = INT_MAX;
    int market_idx = 0;


    for(int i = 0; i<markets.size(); i++) {
        if(shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0] < min_route) {
            min_route = shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0];
            market_idx = markets[i].point_idx;
        }
    }
    return Path(1,market_idx);
}

QVector <QVector <int> > DijkstrasAlg::getPaths() {
    return shortestPaths;
}

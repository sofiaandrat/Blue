#include "dijkstrasalg.h"
#include <iostream>
#include <QDebug>


DijkstrasAlg::DijkstrasAlg(int townIdx, QVector<QVector<int> > &Table, QVector<int> &pointsOfGraph)
{
    int n = pointsOfGraph.size();
    this->pointsOfGraph = pointsOfGraph;
   // qDebug() << pointsOfGraph;
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
   // qDebug() << shortestPaths;
   // qDebug() << path;
    for(int i = pointsOfGraph.indexOf(pointIdx); shortestPaths[i][1] != 0; i = shortestPaths[i][1])
    {
        path.append(shortestPaths[i][1]);
    }
    path.append(0);

  //  qDebug() << path;
    if(fromTown)
    {
        std::reverse(path.begin(),path.end());
    }
    for(int i = 0; i < path.size(); i++)
        qDebug() << path[i];
    return path;
}

QVector<int>  DijkstrasAlg::PathToNearestMarket(QVector<market> markets){
    int min_route = INT_MAX;
    int market_idx = 0;


    for(int i = 0; i<markets.size(); i++)
    {
        if(shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0] < min_route)
        {
            min_route = shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0];
            market_idx = markets[i].point_idx;
        }
    }
    return Path(1,market_idx);
}

QVector <QVector <int> > DijkstrasAlg::getPaths() {
    return shortestPaths;
}

QVector <int> DijkstrasAlg::Moving(Map1 map)
{
    QVector <market> markets;
    markets = map.getterMarkets();
    QVector <market> rating_shops(1);
    QVector <market> black_rating_shops(1);
    QVector <int> storage_shops;
    for (int i = 0; i < markets.size(); i++)
    {
        markets[i].mark = markets[i].product / shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0];
        //rating_shops.resize(rating_shops.size() + 1);
        for(int j = 0; j < rating_shops.size(); j++)
        {
            qDebug() << shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0];
            if (markets[i].mark == 0)
                continue;
            if (map.getProducts() < shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0] * (map.getPopulation() + ((2 * shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0]) / 30)))
            {
                black_rating_shops.insert(j,markets[i]);
                break;
            }
            if(rating_shops[j].mark < markets[i].mark)
            {
                rating_shops.insert(j,markets[i]);
                break;
            }
            if(rating_shops[j].mark == markets[i].mark)
            {
                if(shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0] < shortestPaths[pointsOfGraph.indexOf(rating_shops[j].point_idx)][0])
                    rating_shops.insert(j,markets[i]);
                else
                    rating_shops.insert(j + 1,markets[i]);
                break;
            }
        }
    }
    rating_shops.pop_back();
    black_rating_shops.pop_back();
    for(int i = 0; i < rating_shops.size(); i++)
        qDebug() << rating_shops[i].mark << " " << rating_shops[i].point_idx;
    if(rating_shops.isEmpty())
        return Path(1,black_rating_shops[0].point_idx);
    return Path(1,rating_shops[0].point_idx);
}

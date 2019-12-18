#include "strategy.h"
#include "dijkstrasalg.h"
#include "dijkstrasalg.cpp"
Strategy::Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts):alg(townIdx, Table, pointsOfGraph, posts)
{
    this->pointsOfGraph = pointsOfGraph;
    this->shortestPaths = alg.getPaths();
}

QVector <int> Strategy::Moving(Map1 map)
{
    QVector <market> markets;
    markets = map.getterMarkets();
    QVector <market> rating_shops(1);
    QVector <market> black_rating_shops(1);
    QVector <int> storage_shops;
    qDebug() << markets.size();
    for (int i = 0; i < markets.size(); i++)
    {
        markets[i].mark = markets[i].product / shortestPaths[pointsOfGraph.indexOf(markets[i].point_idx)][0];
        for(int j = 0; j < rating_shops.size(); j++)
        {
            if (markets[i].mark == 0)
            {
                rating_shops.push_back(markets[i]);
                break;
            }
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
        qDebug() << rating_shops[i].mark;
    if(rating_shops.isEmpty())
        return alg.Path(1,black_rating_shops[0].point_idx);
    else
        return alg.Path(1,rating_shops[0].point_idx);
}

QVector<int>  Strategy::PathToNearestMarket(QVector<market> markets)
{
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
    return alg.Path(1,market_idx);
}

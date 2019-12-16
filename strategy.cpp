#include "strategy.h"
#include "dijkstrasalg.h"
#include "sockettest.h"
Strategy::Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts, SocketTest *socket)
    :alg(townIdx, Table, pointsOfGraph, posts)
{
    this->pointsOfGraph = pointsOfGraph;
    this->shortestPaths = alg.getPaths();
    this->socket = socket;
}

QVector <int> Strategy::Moving(Map1 map, Player player)
{
    QVector <market> markets = map.getterMarkets();
    QVector <market> storages = map.getterStorages();
    QVector <train> upgradeTrains;
    market Market = BestPost(map, markets);
    market Storage = BestPost(map, storages);
    qDebug() << storages.size();
    int lengthOfPathToMarket = shortestPaths[pointsOfGraph.indexOf(Market.point_idx)][0];
    qDebug() << pointsOfGraph.indexOf(Market.point_idx) << " " << shortestPaths.size();
    int lengthOfPathToStorage = shortestPaths[pointsOfGraph.indexOf(Storage.point_idx)][0];
    if(map.getLevel() < player.getPlayerTrains()[0].level)
    {
        if(map.getPrice() <= map.getArmor())
        {
            if(map.getArmor() - map.getPrice() > player.getPlayerTrains()[0].price)
                upgradeTrains.push_back(player.getPlayerTrains()[0]);
            socket->sendUpgradeMessage(true, upgradeTrains, player.getPlayerData().home_idx);
        } else if (player.getPlayerTrains()[0].price < map.getArmor())
        {
            upgradeTrains.push_back(player.getPlayerTrains()[0]);
            socket->sendUpgradeMessage(true, upgradeTrains, player.getPlayerData().home_idx);
        }
        map = *new Map1();
        map.Pars(socket->getterDoc());
    }
    int needProducts = (map.getPopulation() + (2 * (lengthOfPathToMarket + lengthOfPathToStorage) / 30)) * (lengthOfPathToMarket + lengthOfPathToStorage);
    if(map.getProducts() > needProducts)
        return alg.Path(1, Storage.point_idx);
    else
        return alg.Path(1, Market.point_idx);

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

market Strategy::BestPost(Map1 map, QVector <market> posts)
{
    QVector <market> rating(1);
    QVector <market> black_rating(1);
    for (int i = 0; i < posts.size(); i++)
    {
        posts[i].mark = posts[i].goods / shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]; //не надо дальноглядности, тчобы не посадить себя на крючок
        for(int j = 0; j < rating.size(); j++)
        {
            if (posts[i].mark == 0)
            {
                rating.push_back(posts[i]);
                break;
            }
            if (map.getProducts() < shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * (map.getPopulation() + ((2 * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]) / 30)))
            {
                black_rating.insert(j,posts[i]);
                break;
            }
            if(rating[j].mark < posts[i].mark)
            {
                rating.insert(j,posts[i]);
                break;
            }
            if(rating[j].mark == posts[i].mark)
            {
                if(shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] < shortestPaths[pointsOfGraph.indexOf(rating[j].point_idx)][0])
                    rating.insert(j,posts[i]);
                else
                    rating.insert(j + 1,posts[i]);
                break;
            }
        }
    }
    rating.pop_back();
    black_rating.pop_back();
    for(int i = 0; i < rating.size(); i++)
        qDebug() << rating[i].mark;
    if(rating.isEmpty())
        return black_rating[0];
    else
        return rating[0];
}

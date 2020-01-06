#include "strategy.h"
#include "dijkstrasalg.h"
#include "dijkstrasalg.cpp"
Strategy::Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts, SocketTest *socket):alg(townIdx, Table, pointsOfGraph, posts)
{
    this->pointsOfGraph = pointsOfGraph;
    this->shortestPaths = alg.getPaths();
    this->socket = socket;
}

QVector <int> Strategy::Moving(Map1 map, Player player)
{
    this->shortestPaths = alg.getPaths();
    QVector <market> markets = map.getterMarkets();
    QVector <market> storages = map.getterStorages();
    QVector <train> upgradeTrains;
    QVector <market> GoodMarkets = GoodPosts(map, markets, player);
    QVector <int> pointsToVisit(0);
    QVector <int> pointsToAvoid(0);
    if(GoodMarkets.empty())
        GoodMarkets = markets;
    market Market = BestPost(map, GoodMarkets, player);
    market Storage = BestPost(map, storages, player);
    int lengthOfPathToMarket = shortestPaths[pointsOfGraph.indexOf(Market.point_idx)][0];
    int lengthOfPathToStorage = shortestPaths[pointsOfGraph.indexOf(Storage.point_idx)][0];
    if(map.getHome(player.getPlayerData().player_idx).level < player.getPlayerTrains()[0].level && map.getHome(player.getPlayerData().player_idx).price != 0)
    {
        if(map.getHome(player.getPlayerData().player_idx).price <= map.getHome(player.getPlayerData().player_idx).armor)
        {
            if(map.getHome(player.getPlayerData().player_idx).armor - map.getHome(player.getPlayerData().player_idx).price > player.getPlayerTrains()[0].price && player.getPlayerTrains()[0].price != 0)
                upgradeTrains.push_back(player.getPlayerTrains()[0]);
            socket->sendUpgradeMessage(true, upgradeTrains, player.getPlayerData().home_post_idx);
        }
    } else if (player.getPlayerTrains()[0].price <= map.getHome(player.getPlayerData().player_idx).armor && player.getPlayerTrains()[0].price != 0)
    {
        upgradeTrains.push_back(player.getPlayerTrains()[0]);
        socket->sendUpgradeMessage(false, upgradeTrains, player.getPlayerData().home_idx);
    }
    socket->SendMessage(MAP,{{"layer", 1}});
    map = *new Map1();
    map.Pars(socket->getterDoc());
    QVector <train> Trains = map.getTrains();
    QVector <train> NewTrainsInfo;
    for(int i = 0; i < Trains.size(); i++)
    {
        if(Trains[i].player_idx == player.getPlayerData().player_idx)
            NewTrainsInfo.append(Trains[i]);
    }
    player.setTrains(NewTrainsInfo);
    int needProducts = (map.getHome(player.getPlayerData().player_idx).population + (2 * (lengthOfPathToMarket + lengthOfPathToStorage) / 25)) * (lengthOfPathToMarket + lengthOfPathToStorage) * 2;
    if(map.getHome(player.getPlayerData().player_idx).products > needProducts)
    {
        for(int i = 0; i < markets.size(); i++)
            pointsToAvoid.append(markets[i].point_idx);
        return alg.manipPaths(player.getPlayerData().home_idx, Storage.point_idx,pointsToVisit,pointsToAvoid);
    }
    else
    {
        for(int i = 0; i <storages.size(); i++)
            pointsToAvoid.append(storages[i].point_idx);
        return alg.manipPaths(player.getPlayerData().home_idx, Market.point_idx,pointsToVisit,pointsToAvoid);
    }

}

market Strategy::BestPost(Map1 map, QVector <market> posts, Player player)
{
    QVector <market> rating(1);
    QVector <market> black_rating(1);
    for (int i = 0; i < posts.size(); i++)
    {
        posts[i].mark = posts[i].goods / this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]; //не надо дальноглядности, тчобы не посадить себя на крючок
        for(int j = 0; j < rating.size(); j++)
        {
            if (posts[i].mark == 0)
            {
                rating.insert(rating.size() - 1, posts[i]);
                break;
            }
            if (map.getHome(player.getPlayerData().player_idx).products < this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * (map.getHome(player.getPlayerData().player_idx).population + ((2 * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]) / 25)))
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
                if(this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] < this->shortestPaths[pointsOfGraph.indexOf(rating[j].point_idx)][0]) {
                    rating.insert(j,posts[i]);
                }
                else {
                    if((j+1) == rating.size()) {
                        rating.push_back(posts[i]);
                    } else {
                        rating.insert(j + 1,posts[i]);
                    }
                }
                break;
            }
        }
    }
    rating.pop_back();
    black_rating.pop_back();
    if(rating.isEmpty())
        return black_rating[0];
    else
       return rating[0];
}

QVector <market> Strategy::GoodPosts(Map1 map, QVector <market> posts, Player player)
{
    QVector <market> rating;
    for(int i = 0; i < posts.size(); i++)
    {
        posts[i].mark = map.getHome(player.getPlayerData().player_idx).population * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * 2;
        if(posts[i].mark < posts[i].goods)
        {
            rating.append(posts[i]);
        }
    }
    return rating;
}

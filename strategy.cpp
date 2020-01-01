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
    QVector <market> GoodMarkets = GoodPosts(map, markets);
    if(GoodMarkets.empty())
        GoodMarkets = markets;
    market Market = BestPost(map, GoodMarkets);
    market Storage = BestPost(map, storages);
    int lengthOfPathToMarket = shortestPaths[pointsOfGraph.indexOf(Market.point_idx)][0];
    int lengthOfPathToStorage = shortestPaths[pointsOfGraph.indexOf(Storage.point_idx)][0];
    if(map.getLevel() < map.getTrains()[0].level && map.getPrice() != 0)
    {
        if(map.getPrice() <= map.getArmor())
        {
            if(map.getArmor() - map.getPrice() > map.getTrains()[0].price &&
                    map.getTrains()[0].price != 0)
                upgradeTrains.push_back(map.getTrains()[0]);
            socket->sendUpgradeMessage(true, upgradeTrains, player.getPlayerData().home_post_idx);
        }
    } else if (map.getTrains()[0].price <= map.getArmor() && map.getTrains()[0].price != 0)
    {
        qDebug() << map.getTrains()[0].price << " " << map.getArmor();
        upgradeTrains.push_back(map.getTrains()[0]);
        socket->sendUpgradeMessage(false, upgradeTrains, player.getPlayerData().home_idx);
    }
    socket->SendMessage(MAP,{{"layer", 1}});
    map = *new Map1();
    map.Pars(socket->getterDoc());
    int needProducts = (map.getPopulation() + (2 * (lengthOfPathToMarket + lengthOfPathToStorage) / 30)) * (lengthOfPathToMarket + lengthOfPathToStorage) * 2;
    if(map.getProducts() > needProducts)
        return alg.Path(1, Storage.point_idx);
    else
        return alg.Path(1, Market.point_idx);
}

market Strategy::BestPost(Map1 map, QVector <market> posts)
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
            if (map.getProducts() < this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * (map.getPopulation() + ((2 * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]) / 30)))
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
                if(this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] < this->shortestPaths[pointsOfGraph.indexOf(rating[j].point_idx)][0])
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

QVector <market> Strategy::GoodPosts(Map1 map, QVector <market> posts)
{
    QVector <market> rating;
    for(int i = 0; i < posts.size(); i++)
    {
        posts[i].mark = map.getPopulation() * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * 2;
        if(posts[i].mark < posts[i].goods)
        {
            rating.append(posts[i]);
        }
    }
    return rating;
}

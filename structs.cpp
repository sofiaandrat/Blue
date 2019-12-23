#include "structs.h"
#include <QDebug>

void Map0::Pars(QJsonDocument doc)
{
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["points"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        this->pointsOfGraph.append(obj["idx"].toInt());
    }
    jsonArray = jsonObject["lines"].toArray();
    QVector <QVector <int> > Layer0(pointsOfGraph.size(), QVector <int> (pointsOfGraph.size()));
    this->Table = Layer0;
    Layer0.clear();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        int i = (obj["points"].toArray())[0].toInt();
        int j = (obj["points"].toArray())[1].toInt();
        for(int i1 = 0; i1 < this->pointsOfGraph.size(); i1++)
        {
            if(i == this->pointsOfGraph[i1])
            {
                i = i1;
            }
            if(j == this->pointsOfGraph[i1])
            {
                j = i1;
            }
        }

        //3rd
        if(i < j) {
            this->Table[i][j] = obj["length"].toInt();
            this->Table[j][i] = obj["idx"].toInt();
        } else {
            this->Table[j][i] = obj["length"].toInt();
            this->Table[i][j] = obj["idx"].toInt()*(-1);
        }
    }
}
QVector <int> Map0::getterPointsOfgraph()
{
    return pointsOfGraph;
}
QVector <QVector <int> > Map0::getterTable()
{
    return Table;
}

void Map1::Pars(QJsonDocument doc)
{
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["posts"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        post Post;
        Post.point_idx = obj["point_idx"].toInt();
        Post.idx = obj["idx"].toInt();
        Post.type = obj["type"].toInt();
        this->Posts.append(Post);
        if(obj["type"] == TOWN)
        {
            this->population = obj["population"].toInt();
            this->products = obj["product"].toInt();
            this->armor = obj["armor"].toInt();
            this->level = obj["level"].toInt();
            this->price = obj["next_level_price"].toInt();
        }
        if(obj["type"].toInt() == MARKET) {
            market Market;
            Market.idx = obj["idx"].toInt();
            Market.point_idx = obj["point_idx"].toInt();
            Market.goods = obj["product"].toInt();
            Market.goods_capacity = obj["product_capacity"].toInt();
            Market.replenishment = obj["replenishment"].toInt();
            Market.type = obj["type"].toInt();
            Market.name = obj["name"].isString();
            Market.mark = 0;
            this->Markets.append(Market);
        }
        if(obj["type"].toInt() == STORAGE) {
            market Storage;
            Storage.idx = obj["idx"].toInt();
            Storage.point_idx = obj["point_idx"].toInt();
            Storage.goods = obj["armor"].toInt();
            Storage.goods_capacity = obj["armor_capacity"].toInt();
            Storage.replenishment = obj["replenishment"].toInt();
            Storage.type = obj["type"].toInt();
            Storage.name = obj["name"].isString();
            Storage.mark = 0;
            this->Storages.append(Storage);
        }

    }
    jsonArray = jsonObject["trains"].toArray();
    foreach(const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        train Train;
        Train.player_idx = obj["player_idx"].toString();
        Train.idx = obj["idx"].toInt();
        Train.goods = obj["goods"].toInt();
        Train.goods_capacity = obj["goods_capacity"].toInt();
        Train.goods_type = obj["goods_type"].toInt();
        Train.line_idx = obj["line_idx"].toInt();
        Train.position = obj["position"].toInt();
        Train.speed = obj["speed"].toInt();
        Train.level = obj["level"].toInt();
        Train.price = obj["next_level_price"].toInt();
        this->AllTrains.append(Train);
    }

}

QVector <post> Map1::getterPosts()
{
    return this->Posts;
}

QVector <market> Map1::getterMarkets()
{
    return this->Markets;
}

QVector <market> Map1::getterStorages()
{
    return this->Storages;
}
void Player::Pars(QJsonDocument doc) {
    QJsonObject jsonObject = doc.object();
    //town Town;
    QJsonObject jsonHomeObject = jsonObject["home"].toObject();
    this->playerData.home_idx = jsonHomeObject["idx"].toInt();
    this->playerData.home_post_idx = jsonHomeObject["post_idx"].toInt();

    this->playerData.idx = jsonObject["idx"].toString();
    this->playerData.in_game = jsonObject["in_game"].toBool();
    this->playerData.name = jsonObject["name"].toString();
    this->playerData.rating = jsonObject["rating"].toInt();

    QJsonArray jsonArray = jsonObject["trains"].toArray();
    foreach(const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        train Train;
        Train.player_idx = obj["player_idx"].toString();
        Train.idx = obj["idx"].toInt();
        Train.goods = obj["goods"].toInt();
        Train.goods_capacity = obj["goods_capacity"].toInt();
        Train.goods_type = obj["goods_type"].toInt();
        Train.line_idx = obj["line_idx"].toInt();
        Train.position = obj["position"].toInt();
        Train.speed = obj["speed"].toInt();
        Train.level = obj["level"].toInt();
        Train.price = obj["next_level_price"].toInt();
        this->playerTrains.append(Train);
    }
}

player Player::getPlayerData()
{
    return playerData;
}

QVector<train> Player::getPlayerTrains() {
    return playerTrains;
}

int Map1::getTick() {
    return this->tick;
}

int Map1::getPopulation()
{
    return this->population;
}
int Map1::getProducts()
{
    return this->products;
}

int Map1::getArmor()
{
    return this->armor;
}

int Map1::getLevel()
{
    return this->level;
}

int Map1::getPrice()
{
    return this->price;
}

QVector <train> Map1::getTrains()
{
    return this->AllTrains;
}

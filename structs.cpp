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

        if(obj["type"].toInt() == 2) {
            market Market;
            Market.idx = obj["idx"].toInt();
            Market.point_idx = obj["point_idx"].toInt();
            Market.product = obj["product"].toInt();
            Market.product_capacity = obj["product_capacity"].toInt();
            Market.replenishment = obj["replenishment"].toInt();
            Market.type = obj["type"].toInt();
            Market.name = obj["name"].isString();
            this->Markets.append(Market);
        }

    }
    jsonArray = jsonObject["trains"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        train Train;
        Train.goods = obj["goods"].toInt();
        Train.speed = obj["speed"].toInt();
        Train.line_idx = obj["line_idx"].toInt();
        Train.goods_capacity = obj["goods_capacity"].toInt();
    }

}

QVector <post> Map1::getterPosts()
{
    return Posts;
}

QVector <market> Map1::getterMarkets()
{
    return Markets;
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
        this->playerTrains.append(Train);
    }
}

player Player::getPlayerData() {
    return playerData;
}

QVector<train> Player::getPlayerTrains() {
    return playerTrains;
}

int Map1::getTick() {
    return this->tick;
}

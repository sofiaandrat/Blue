#include "structs.h"

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
        this->Table[i][j] = obj["length"].toInt();
        this->Table[j][i] = this->Table[i][j];
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
        Post.product = obj["product"].toInt();
        Post.product_capacity = obj["product_capacity"].toInt();
        Post.replenishment = obj["replenishment"].toInt();
        Post.type = obj["type"].toInt();
        Post.name = obj["name"].isString();
        this->Posts.append(Post);
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

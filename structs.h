#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Map0 //если будет нужно позже я добавлю те пункты, пока что их предназначение в это мире не ясно
{
private:
    QVector <int> pointsOfGraph;
    QVector <QVector <int> > Table;
public:
    Map0(){}
    void Pars(QJsonDocument doc);
    QVector <int> getterPointsOfgraph();
    QVector <QVector <int> > getterTable();
};

struct post //когда нам понадобяться остальные данные придётся немного по-другому сделать, но идея та же
{
  QString name;
  int point_idx;
  int product;
  int product_capacity;
  int replenishment;
  int type;
};
struct train
{
    int goods;
    int goods_capacity;
    int line_idx;
    int speed;
};

class Map1
{
private:
    QVector <post> Posts;
    QVector <train> Trains;
public:
    Map1(){}
    void Pars(QJsonDocument doc);
    QVector <post> getterPosts();
    QVector <train> getterTrains();
};

#endif // STRUCTS_H

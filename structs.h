#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

struct town
{
    int idx;
    int armor;
    int armor_capacity;
    QString name;
    QString player_idx;
    int point_idx;
    int population;
    int population_capacity;
    int type;
};

struct player
{
    QString idx;
    bool in_game;
    QString name;
    int rating;
    int home_idx;
    int home_post_idx;
};

struct train
{
    QString player_idx;
    int idx;
    int goods;
    int goods_capacity;
    int goods_type;
    int line_idx;
    int position;
    int speed;
};

class Player
{
private:
    player playerData;
    QVector<train> playerTrains;
public:
    Player(){}
    void Pars(QJsonDocument doc);
    player getPlayerData();
    QVector <train> getPlayerTrains();
};

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

struct market
{
  QString name;
  int idx;
  int point_idx;
  int product;
  int product_capacity;
  int replenishment;
  int type;
  int mark;
};

struct post //когда нам понадобяться остальные данные придётся немного по-другому сделать, но идея та же
{
  int idx;
  int point_idx;
  int type;
};

class Map1
{
private:
    QVector <post> Posts;
    QVector <market> Markets;
    QVector <train> AllTrains;
    int tick;
    int population;
    int products;
    int armor;
public:
    Map1(){}
    void Pars(QJsonDocument doc);
    QVector <post> getterPosts();
    QVector <train> getterAllTrains();
    QVector <market> getterMarkets();
    int getTick();
    int getPopulation();
    int getProducts();
    int getArmor();
};

#endif // STRUCTS_H

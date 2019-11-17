#ifndef PARSER_H
#define PARSER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVector>
#include "mainwindow.h"
#include <QDebug>

class parser
{
private:
    QVector <int> pointsOfGraph;
    QVector <QVector <int> > Layer0;
    QVector <QVector <int> > Layer1;
public:
    parser();
    void Pars(QJsonDocument doc);
    QVector <int> getterPointsOfGraph();
    QVector <QVector <int> > getterLayer0();
    QVector <QVector <int> > getterLayer1();
};

#endif // PARSER_H

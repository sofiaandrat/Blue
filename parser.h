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
    QVector <QVector <int> > Table;
public:
    parser();
    void Pars(QJsonDocument doc, MainWindow* window);
    QVector <int> getterPointsOfGraph();
    QVector <QVector <int> > getterTable();
};

#endif // PARSER_H

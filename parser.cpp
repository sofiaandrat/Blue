#include "parser.h"
#include "graphwidget.h"
#include "mainwindow.h"
parser::parser()
{
}
void parser::Pars(QJsonDocument doc, MainWindow* window)
{

    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["points"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        this->pointsOfGraph.append(obj["idx"].toInt());
    }
    QVector <QVector <int> > Table(pointsOfGraph.size(), QVector <int> (pointsOfGraph.size()));
    this->Table = Table;
    Table.clear();
    jsonArray = jsonObject["lines"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        int i = (obj["points"].toArray())[0].toInt();
        int j = (obj["points"].toArray())[1].toInt();
        for(int i1 = 0; i1 < this->pointsOfGraph.size(); i1++) {
            if(i == this->pointsOfGraph[i1]) {
                i = i1;
            }
            if(j == this->pointsOfGraph[i1]) {
                j = i1;
            }
        }
        this->Table[i][j] = obj["length"].toInt();
        this->Table[j][i] = this->Table[i][j];
    }
    //qDebug() << this->pointsOfGraph;
    new GraphWidget(nullptr, this->Table, this->pointsOfGraph, window);
}

QVector <int> parser::getterPointsOfGraph()
{
    return this->pointsOfGraph;
}

QVector <QVector <int> > parser::getterTable()
{
    return this->Table;
}

#include "parser.h"
#include "graphwidget.h"
#include "mainwindow.h"
parser::parser()
{
}
void parser::Pars(QJsonDocument doc)
{

    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["points"].toArray();
    if(!jsonArray.isEmpty())
    {
        foreach(const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            this->pointsOfGraph.append(obj["idx"].toInt());
        }
    }
    jsonArray = jsonObject["lines"].toArray();
    if(!jsonArray.isEmpty()) //первый раз
    {
        QVector <QVector <int> > Layer0(pointsOfGraph.size(), QVector <int> (pointsOfGraph.size()));
        this->Layer0 = Layer0;
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
            this->Layer0[i][j] = obj["length"].toInt();
            this->Layer0[j][i] = this->Layer0[i][j];
        }
    }
    jsonArray = jsonObject["posts"].toArray();
    if(!jsonArray.isEmpty()) // второй раз, в следующий раз напишем что-то изящное!!!
    {
        foreach(const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            QVector <int> a(2);
            a[0] = obj["point_idx"].toInt();
            a[1] = obj["type"].toInt();
            Layer1.push_back(a);
            a.clear();
        }
    }
}

QVector <int> parser::getterPointsOfGraph()
{
    return this->pointsOfGraph;
}

QVector <QVector <int> > parser::getterLayer0()
{
    return this->Layer0;
}

QVector <QVector <int> > parser::getterLayer1()
{
    return this->Layer1;
}

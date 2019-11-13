#include "mainwindow.h"
#include "graphwidget.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_json_file_triggered()
{
    globpath = QFileDialog::getOpenFileName(this, tr(""),"",  tr("*.json"));
    file.setFileName(globpath);
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close();
        if(docError.errorString().toInt() == QJsonParseError::NoError)
        {
            QJsonObject jsonObject = doc.object();
            //ui->label->setText(jsonObject["name"].toString());
            QJsonArray jsonArray = jsonObject["points"].toArray();
            QVector <int> pointsOfGraph;
            foreach(const QJsonValue & value, jsonArray)
            {
                QJsonObject obj = value.toObject();
                pointsOfGraph.append(obj["idx"].toInt());
            }
            QVector <QVector <int> > Table(pointsOfGraph.size(), QVector <int> (pointsOfGraph.size()));
            jsonArray = jsonObject["lines"].toArray();
            foreach(const QJsonValue & value, jsonArray)
            {
                QJsonObject obj = value.toObject();
                int i = (obj["points"].toArray())[0].toInt();
                int j = (obj["points"].toArray())[1].toInt();
                for(int i1 = 0; i1 < pointsOfGraph.size(); i1++) {
                    if(i == pointsOfGraph[i1]) {
                        i = i1;
                    }
                    if(j == pointsOfGraph[i1]) {
                        j = i1;
                    }
                }

                Table[i][j] = obj["length"].toInt();
                Table[j][i] = Table[i][j];
            }

            new GraphWidget(0,Table,pointsOfGraph,this);
        }

    }
    else
    {
        QMessageBox::information(nullptr,"info","file wasn't open");
    }
}

#include "mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    SocketTest Socket;
    Socket.Connect();
    Socket.SendMessage(LOGIN,{{"name", ui->login->text()}});
    Socket.SendMessage(MAP,{{"layer", 0}});
    Map0 Layer0;
    Layer0.Pars(Socket.getterDoc());
    QVector <int> pointsOfGraph = Layer0.getterPointsOfgraph();
    QVector <QVector <int> > Table = Layer0.getterTable();
    Socket.SendMessage(MAP,{{"layer", 1}});
    Map1 Layer1;
    Layer1.Pars(Socket.getterDoc());
    QVector <QVector <int> > pointsType = Layer1.getterPosts();//!!!! надо переработать в отрисовке принцип принятия данных
    //new GraphWidget(nullptr, Table, pointsOfGraph, pointsType, this);
}

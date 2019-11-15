#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sockettest.h"
#include "parser.h"
#include "graphwidget.h"
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
    parser Parser;
    Socket.Connect();
    Socket.SendMessage(LOGIN,{{"name", ui->login->text()}});
    Socket.SendMessage(MAP,{{"layer", 0}});
    Parser.Pars(Socket.getterDoc(),this);
    Socket.SendMessage(MAP,{{"layer", 1}});
    Socket.SendMessage(MAP,{{"layer", 10}});
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sockettest.h"

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
    Socket.SendMessage1(MAP, {{"layer", 0}});
}

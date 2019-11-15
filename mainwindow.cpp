#include "mainwindow.h"
#include "graphwidget.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>
#include "sockettest.h"

>>>>>>> First commit
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
}

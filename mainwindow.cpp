#include "mainwindow.h"
#include "graphwidget.h"
//#include <QThread>

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
    SocketTest *Socket = new SocketTest(this);
    Socket->Connect();
    QString loginText = ui->login->text();
    new GraphWidget(nullptr,*Socket,loginText,this);
}

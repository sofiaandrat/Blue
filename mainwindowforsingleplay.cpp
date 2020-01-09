#include "mainwindowforsingleplay.h"
#include "ui_mainwindowforsingleplay.h"
#include "graphwidget.h"

MainWindowForSinglePlay::MainWindowForSinglePlay(QMainWindow *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForSinglePlay)
{
    this->Socket = new SocketTest(this);
    this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ui->setupUi(this);
    this->show();
  //  MainWindowForSinglePlay *presenter = new MainWindowForSinglePlay(this);
}

MainWindowForSinglePlay::~MainWindowForSinglePlay()
{
    delete ui;
}

void MainWindowForSinglePlay::on_pushButton_clicked()
{

    QString loginText = this->getLoginText();
    Game.gameName = "Game of " + this->getLoginText();
    new GraphWidget(nullptr, *(this->getSocket()), this, loginText);
}

QString MainWindowForSinglePlay::getLoginText()
{
    return ui->login->text();
}

void MainWindowForSinglePlay::on_back_clicked()
{
    AskSelect *askSelect = new AskSelect();
    askSelect->show();
    this->close();
}

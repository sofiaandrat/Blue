#include "View/mainwindowforsingleplay.h"
#include "ui_mainwindowforsingleplay.h"
#include "graphwidget.h"

MainWindowForSinglePlay::MainWindowForSinglePlay(QMainWindow *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForSinglePlay)
{
//    this->Socket = new SocketTest(this);
//    this->Socket->Connect();
//    this->Socket->SendMessage(GAMES,{});
    SinglePlayerPresenter *presenter = new SinglePlayerPresenter(this, new SocketService());
    ui->setupUi(this);
    this->show();
}

MainWindowForSinglePlay::~MainWindowForSinglePlay()
{
    delete ui;
}

void MainWindowForSinglePlay::on_pushButton_clicked()
{

    /*QString loginText = this->getLoginText();
    Game.gameName = "Game of " + this->getLoginText();
    new GraphWidget(nullptr, *(this->getSocket()), this, loginText);*/
    emit StartGame();
}

QString MainWindowForSinglePlay::getLoginText()
{
    return "Game of " + ui->login->text();
}

void MainWindowForSinglePlay::on_back_clicked()
{
    emit BackPush();
    this->close();
}

QJsonObject MainWindowForSinglePlay::getLoginData()
{
    QString loginText = getLoginText();
    return {{"name", loginText}};
}

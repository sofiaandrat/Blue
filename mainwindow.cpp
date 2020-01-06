#include "mainwindow.h"
#include "graphwidget.h"
//#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
   // , ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
   // delete ui;
}

game MainWindow::getGame()
{
    //this->Socket = new SocketTest(this);
    //this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(this->Socket->getterDoc());
    QVector <game> Games = games.getGames();
    for(int i = 0; i < Games.size(); i++)
    {
        if(Games[i].gameName == this->Game.gameName)
            return Games[i];
    }
}

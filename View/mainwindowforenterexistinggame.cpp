#include "mainwindowforenterexistinggame.h"
#include "ui_mainwindowforenterexistinggame.h"

MainWindowForEnterExistingGame::MainWindowForEnterExistingGame(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForEnterExistingGame)
{
    this->Socket = new SocketTest(this);
    this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(this->Socket->getterDoc());
    QStringList GameList;
    this->gameList = games.getGames();
    ui->setupUi(this);
    for(int i = 0; i < gameList.size(); i++)
    {
        GameList.append(this->gameList[i].gameName);
    }
    ui->gameList->addItems(GameList);
    this->show();

}

MainWindowForEnterExistingGame::~MainWindowForEnterExistingGame()
{
    delete ui;
}

void MainWindowForEnterExistingGame::on_refresh_clicked()
{
    this->Socket->SendMessage(GAMES,{});
    ui->gameList->clear();
    ExistingGames games;
    games.Pars(this->Socket->getterDoc());
    QStringList GameList;
    this->gameList = games.getGames();
    for(int i = 0; i < gameList.size(); i++)
    {
        GameList.append(this->gameList[i].gameName);
    }
    ui->gameList->addItems(GameList);
}

void MainWindowForEnterExistingGame::on_login_clicked()
{
    QString loginText = ui->login->text();
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setText("Something");
    label->setGeometry(QRect(10,10,30,80));
    Game->gameName = ui->gameList->currentText();
   // new GraphWidget(nullptr, *(this->Socket), this, ui->login->text(), ui->gameList->currentText());
}

void MainWindowForEnterExistingGame::on_back_clicked()
{
    AskSelect *askSelect = new AskSelect();
    askSelect->show();
    this->close();
}

QJsonObject MainWindowForEnterExistingGame::getLoginData()
{
    return *(new QJsonObject);
}

game* MainWindowForEnterExistingGame::getGame()
{
    game* Game;
    return Game;
}

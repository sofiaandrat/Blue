#include "mainwindowforcreatemultigame.h"
#include "ui_mainwindowforcreatemultigame.h"

MainWindowForCreateMultigame::MainWindowForCreateMultigame(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForCreateMultigame)
{
    this->Socket = new SocketTest(this);
    this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ui->setupUi(this);
    this->show();
}

MainWindowForCreateMultigame::~MainWindowForCreateMultigame()
{
    delete ui;
}

void MainWindowForCreateMultigame::on_loginButton_clicked()
{
    QString loginText = ui->login->text();
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setText("Something");
    label->setGeometry(QRect(10,10,30,80));
    Game->gameName = ui->gameName->text();
    //new GraphWidget(nullptr, *(this->Socket), this, ui->login->text(), ui->gameName->text(), ui->numberOfPlayers->text().toInt(),
                    //ui->numberOfTurns->text().toInt());
}


void MainWindowForCreateMultigame::on_back_clicked()
{
    AskSelect *askSelect = new AskSelect();
    askSelect->show();
    this->close();
}

QJsonObject MainWindowForCreateMultigame::getLoginData()
{
    return *(new QJsonObject());
}

game* MainWindowForCreateMultigame::getGame()
{
    game* Game;
    return Game;
}

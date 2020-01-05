#include "mainwindowforsingleplay.h"
#include "ui_mainwindowforsingleplay.h"
#include "graphwidget.h"

MainWindowForSinglePlay::MainWindowForSinglePlay(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForSinglePlay)
{
    this->Socket = new SocketTest(this);
    this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ui->setupUi(this);
}

MainWindowForSinglePlay::~MainWindowForSinglePlay()
{
    delete ui;
}

void MainWindowForSinglePlay::on_pushButton_clicked()
{
    QString loginText = ui->login->text();
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setText("Something");
    label->setGeometry(QRect(10,10,30,80));
    new GraphWidget(nullptr, *(this->Socket), this, loginText);
}

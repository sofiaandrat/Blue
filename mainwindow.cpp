#include "mainwindow.h"
#include "graphwidget.h"
//#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->Socket = new SocketTest(this);
    this->Socket->Connect();
    this->Socket->SendMessage(GAMES,{});
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString loginText = ui->login->text();
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setText("Something");
    label->setGeometry(QRect(10,10,30,80));
    new GraphWidget(nullptr,*(this->Socket),loginText,this);
}

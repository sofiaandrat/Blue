#include "askselect.h"
#include "ui_askselect.h"

AskSelect::AskSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskSelect)
{
    ui->setupUi(this);
}

AskSelect::~AskSelect()
{
    delete ui;
}

void AskSelect::setMainWindow(MainWindow *window)
{
    this->window = window;
}

void AskSelect::on_single_clicked()
{
    this->window = new MainWindowForSinglePlay();
    this->window->show();
    this->close();
}

void AskSelect::on_createMultiplayer_clicked()
{
    this->window = new MainWindowForCreateMultigame();
    this->window->show();
    this->close();
}

void AskSelect::on_enterMultiplayer_clicked()
{
    this->window = new MainWindowForEnterExistingGame();
    this->window->show();
    this->close();
}

#include "singlgamepresenter.h"
#include "mainwindowforsingleplay.h"
SinglGamePresenter::SinglGamePresenter(MainWindow *parent)
{
    connect(&*parent,SIGNAL(StartGame()),this,SLOT(StartGame()));
    //this->window = static_cast<MainWindowForSinglePlay*>(parent);
}

void SinglGamePresenter::StartGame()
{
}

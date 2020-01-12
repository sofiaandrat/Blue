#include "singleplayerpresenter.h"

SinglePlayerPresenter::SinglePlayerPresenter(MainWindow *parent, ISocketService *service)
{
    this->parent = parent;
    this->service = service;
    this->service->OpenConnection();
    connect(&*(this->parent), SIGNAL(StartGame()), this, SLOT(LoginPush()));
    connect(&*(this->parent), SIGNAL(BackPush()), this, SLOT(BackPush()));
}

SinglePlayerPresenter::~SinglePlayerPresenter()
{}

void SinglePlayerPresenter::LoginPush()
{
    service->SendMessage(LOGIN, parent->getLoginData());
}

void SinglePlayerPresenter::BackPush()
{
    AskSelect *window = new AskSelect();
}

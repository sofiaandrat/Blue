#include "singleplayerpresenter.h"

SinglePlayerPresenter::SinglePlayerPresenter(MainWindow *parent, ISocketService *service)
{
    this->parent = parent;
    this->service = service;
    connect(&*(this->parent), SIGNAL(StartGame()), this, SLOT(LoginPush()));
    connect(&*(this->parent), SIGNAL(BackPush()), this, SLOT(BackPush()));
}

SinglePlayerPresenter::~SinglePlayerPresenter()
{}

void SinglePlayerPresenter::LoginPush()
{
    service->OpenConnection();
    service->SendMessage(LOGIN, parent->getLoginData());
    player.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 0}});
    layer0.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 1}});
    Map1 layer1;
    layer1.Pars(service->getDoc());
    player.ParsEnemies(layer1);
    GraphWidget *widget = new GraphWidget(nullptr, parent, player, layer0, layer1);
    connect(&*(widget), SIGNAL(RenderFinished(QVector<Edge *>)), &*(this), SLOT(StartStarter(QVector <Edge *>)));
    widget->Render();
}

void SinglePlayerPresenter::BackPush()
{
    AskSelect *window = new AskSelect();
}

void SinglePlayerPresenter::StartStarter(QVector<Edge *> edgeVec)
{
    starter = new Starter(service, parent->getGame(), player, layer0, edgeVec);
    starter->CheckAndStart();
}

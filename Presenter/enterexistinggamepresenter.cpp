#include "enterexistinggamepresenter.h"

EnterExistingGamePresenter::EnterExistingGamePresenter(MainWindow *parent, ISocketService *service)
{
    this->parent = parent;
    this->service = service;
    connect(&*(this->parent), SIGNAL(StartGame()), this, SLOT(LoginPush()));
    connect(&*(this->parent), SIGNAL(BackPush()), this, SLOT(BackPush()));
    connect(&*(this->parent), SIGNAL(Refresh()), this, SLOT(AskExistingGames()));
}
EnterExistingGamePresenter::~EnterExistingGamePresenter()
{}

void EnterExistingGamePresenter::LoginPush()
{
    service->SendMessage(LOGIN, parent->getLoginData());
    player.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 0}});
    layer0.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 1}});
    Map1 layer1;
    layer1.Pars(service->getDoc());
    player.ParsEnemies(layer1);
    widget = new GraphWidget(nullptr, parent, player, layer0, layer1);
    connect(&*(widget), SIGNAL(RenderFinished(QVector<Edge *>, Player)), &*(this), SLOT(StartStarter(QVector <Edge *>, Player)));
    widget->Render();
}

void EnterExistingGamePresenter::BackPush()
{
    AskSelect *window = new AskSelect();
}

void EnterExistingGamePresenter::StartStarter(QVector<Edge *> edgeVec, Player player)
{
    this->player = player;
    starter = new Starter(service, parent->getGame(), player, layer0, edgeVec);
    connect(&*(starter),SIGNAL(Update(town )),&*(widget),SLOT(Update(town )));
    starter->CheckAndStart();
}

void EnterExistingGamePresenter::AskExistingGames()
{
    service->OpenConnection();
    this->service->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(this->service->getDoc());
    emit ShowGames(games);
}

#include "gamelogic.h"
#include <QTime>
#include "strategy.h"
GameLogic::GameLogic(SocketTest *socket, QVector<Edge *> &edgeVec,Train *imageTrain,Map0 &Layer0, Map1 &Layer1,Player &player):iter(1)
{
    this->layer0 = Layer0;
    this->layer1 = Layer1;
    this->player = player;

    this->socket = socket;
    this->edgeVec = edgeVec;
    this->imageTrain = imageTrain;
    this->pointsOfGraph = layer0.getterPointsOfgraph();
    this->Table = layer0.getterTable();
    this->playerTrain = player.getPlayerTrains()[0];

}

void GameLogic::Alhoritm()
{
    QVector <QVector <int> > Table_sym = Table;
    for(int i = 0; i < Table.size()-1; i++)
    {
        for(int j = i+1; j<Table[i].size();j++)
        {
            Table_sym[i][j] = abs(Table[i][j]);
            Table_sym[j][i] = abs(Table[i][j]);
        }
    }
    int realTownIdx = this->player.getPlayerData().home_idx;
    int townIdx = pointsOfGraph.indexOf(realTownIdx);
    Strategy *strategy = new Strategy(townIdx,Table_sym,pointsOfGraph, layer1.getterPosts(), socket);
    this->curRoute = strategy->Moving(layer1, player);
    this->playerTrain = player.getPlayerTrains()[0];
    if(Table[std::max(curRoute[0],curRoute[1])][std::min(curRoute[0],curRoute[1])] < 0) {
        playerTrain.position = Table[std::min(curRoute[0],curRoute[1])][std::max(curRoute[0],curRoute[1])];
    }
    QTimer *timer = new QTimer(this->socket);
    this->time = timer;
    connect(timer, SIGNAL(timeout()), this, SLOT(trainOneStep()));
    timer->start(1000);
    //return;
}

void GameLogic::trainOneStep() {
        qDebug() <<"CURRENT FUCKING ROUTE"<< curRoute;
        int sourceEdgePoint = curRoute[iter - 1];
        int destEdgePoint = curRoute[iter];
        int curSpeed = 1;
        int destDiff = 0;
        int curEdgeInfo = Table[std::max(sourceEdgePoint, destEdgePoint)][std::min(sourceEdgePoint, destEdgePoint)];
        int curEdgeIdx = std::abs(curEdgeInfo);
        int curEdge;
        for(int i = 0; i < edgeVec.size(); i++)
        {
            if(std::abs(edgeVec[i]->getIdx()) == curEdgeIdx)
            {
                curEdge = i;
                break;
            }
        }
        int curLengh = Table[std::min(sourceEdgePoint, destEdgePoint)][std::max(sourceEdgePoint, destEdgePoint)];
        if((sourceEdgePoint < destEdgePoint) && (curEdgeInfo > 0)) {
             curSpeed = 1;
             destDiff = 0;
         } else if((sourceEdgePoint > destEdgePoint) && (curEdgeInfo > 0)) {
            curSpeed = -1;
            destDiff = curLengh;
         } else if((sourceEdgePoint < destEdgePoint) && (curEdgeInfo < 0)) {
            curSpeed = -1;
            destDiff = curLengh;
         } else if((sourceEdgePoint > destEdgePoint) && (curEdgeInfo < 0)) {
            curSpeed = 1;
            destDiff = 0;
         }
        if(playerTrain.position != (curLengh - destDiff)) {
                socket->sendMoveMessage(curEdgeIdx,curSpeed,playerTrain.idx);
                socket->sendTurnMessage();
                socket->SendMessage(MAP,{{"layer", 1}});
                this->layer1 = *new Map1();
                layer1.Pars(socket->getterDoc());
                QVector <train> Trains = layer1.getTrains();
                QVector <train> NewTrainsInfo;
                for(int i = 0; i < Trains.size(); i++)
                {
                    if(Trains[i].player_idx == player.getPlayerData().player_idx)
                        NewTrainsInfo.append(Trains[i]);
                }
                player.setTrains(NewTrainsInfo);
                if((curLengh - destDiff) == curLengh) {
                    playerTrain.position++;
                    imageTrain->advancePosition(edgeVec[curEdge],curLengh,curSpeed,playerTrain.position);
                } else if((curLengh - destDiff) == 0){
                    playerTrain.position--;
                    imageTrain->advancePosition(edgeVec[curEdge],curLengh,curSpeed,playerTrain.position);
                }

            } else {
            // Разбор стыка рёбер. Не оч красиво, но работает.
            if(iter + 1 < curRoute.size()) {
                if((curRoute[iter] < curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] > 0)) {
                    playerTrain.position = 0;
                    iter++;
                    //continue;
                    trainOneStep();
                } else if ((curRoute[iter] > curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] > 0)) {
                    playerTrain.position = Table[std::min(curRoute[iter], curRoute[iter+1])][std::max(curRoute[iter], curRoute[iter+1])];
                    iter++;
                    //continue;
                    trainOneStep();
                } else if ((curRoute[iter] < curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] < 0)) {
                    playerTrain.position = Table[std::min(curRoute[iter], curRoute[iter+1])][std::max(curRoute[iter], curRoute[iter+1])];
                    iter++;
                    //continue;
                    trainOneStep();
                } else if ((curRoute[iter] > curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] < 0)) {
                    playerTrain.position = 0;
                    iter++;
                    //continue;
                    trainOneStep();
                }
                } else {
                    if(curRoute[iter] == pointsOfGraph.indexOf(player.getPlayerData().home_idx))
                    {
                        this->time->stop();
                        GameLogic *alg = new GameLogic(socket,edgeVec,imageTrain,layer0,layer1,player);
                        alg->Alhoritm();

                    }
                    std::reverse(curRoute.begin(),curRoute.end());
                    iter = 1;
                    //trainOneStep();
                }

        }
}

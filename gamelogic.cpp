#include "gamelogic.h"
#include <QTime>

GameLogic::GameLogic(SocketTest *socket, QVector<Edge *> &edgeVec,Train *imageTrain,Map0 &Layer0, Map1 &Layer1,Player &player):iter(1)
{
    this->layer0 = Layer0;
    this->layer1 = Layer1;
    this->player = player;

    this->socket = socket;
    this->edgeVec = edgeVec;
    this->imageTrain = imageTrain;

    int realTownIdx = this->player.getPlayerData().home_idx;
    this->pointsOfGraph = layer0.getterPointsOfgraph();
    int townIdx = pointsOfGraph.indexOf(realTownIdx);
    this->Table = layer0.getterTable();
    QVector <QVector <int> > Table_sym = Table;

    for(int i = 0; i < Table.size()-1; i++) {
        for(int j = i+1; j<Table[i].size();j++) {
            Table_sym[i][j] = abs(Table[i][j]);
            Table_sym[j][i] = abs(Table[i][j]);
        }
    }

    DijkstrasAlg *dAlg = new DijkstrasAlg(townIdx,Table_sym,pointsOfGraph);
    //this->curRoute = dAlg->PathToNearestMarket(layer1.getterMarkets()); //MAIN ALGO
    this->curRoute = {0, 1, 2, 8, 2, 3};
    this->playerTrain = player.getPlayerTrains()[0];
    qDebug() << curRoute;
    QTimer *timer = new QTimer(this->socket);

    for(int i=0; i<edgeVec.size(); i++) {
        qDebug()<<edgeVec[i]->getIdx();
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(trainOneStep()));
    timer->start(1000);
}

void GameLogic::trainOneStep() {

    int sourceEdgePoint = curRoute[iter-1];
    int destEdgePoint = curRoute[iter];
    int curSpeed = 1;
    int destDiff = 0;
    int curEdgeInfo = Table[std::max(sourceEdgePoint, destEdgePoint)][std::min(sourceEdgePoint, destEdgePoint)];
    int curEdgeIdx = std::abs(curEdgeInfo);
    int curEdge;
    for(int i=0;i<edgeVec.size(); i++){
        if(std::abs(edgeVec[i]->getIdx()) == curEdgeIdx) {
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
                trainOneStep();
            } else if ((curRoute[iter] > curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] > 0)) {
                playerTrain.position = Table[std::min(curRoute[iter], curRoute[iter+1])][std::max(curRoute[iter], curRoute[iter+1])];
                iter++;
                trainOneStep();
            } else if ((curRoute[iter] < curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] < 0)) {
                playerTrain.position = Table[std::min(curRoute[iter], curRoute[iter+1])][std::max(curRoute[iter], curRoute[iter+1])];
                iter++;
                trainOneStep();
            } else if ((curRoute[iter] > curRoute[iter+1]) && (Table[std::max(curRoute[iter], curRoute[iter+1])][std::min(curRoute[iter], curRoute[iter+1])] < 0)) {
                playerTrain.position = 0;
                iter++;
                trainOneStep();
            }
        } else {
            std::reverse(curRoute.begin(),curRoute.end());
            iter = 1;
            trainOneStep();
        }
    }
}

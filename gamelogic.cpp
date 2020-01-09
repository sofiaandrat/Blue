#include "gamelogic.h"
#include <QTime>
#include "strategy.h"
GameLogic::GameLogic(SocketTest *socket, QVector<Edge *> &edgeVec,Train *imageTrain,Map0 &Layer0, Map1 &Layer1,Player &player)
{
    this->layer0 = Layer0;
    this->layer1 = Layer1;
    this->player = player;

    this->socket = socket;
    this->edgeVec = edgeVec;
    this->imageTrain = imageTrain;
    this->pointsOfGraph = layer0.getterPointsOfgraph();
    this->Table = layer0.getterTable();
    //this->playerTrain = player.getPlayerTrains()[0];
    this->prevMap = {};
    //this->animTimer = new QTimeLine(500);
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
    this->strategy = new Strategy(townIdx,Table_sym, pointsOfGraph, layer1.getterPosts(), socket, layer0);
    //strategy->Moving(this->layer1, this->player);
    //this->playerTrain = player.getPlayerTrains()[0];
   /* if(Table[std::max(curRoute[0],curRoute[1])][std::min(curRoute[0],curRoute[1])] < 0) {
        playerTrain.position = Table[std::min(curRoute[0],curRoute[1])][std::max(curRoute[0],curRoute[1])];
    }*/
    trainsOneStep();
    connect(&*(this->socket),SIGNAL(TurnFinished()),this,SLOT(trainsOneStep()));

}

void GameLogic::trainOneStep(train Train) {
       /* socket->SendMessage(MAP,{{"layer",1}});
        QJsonDocument newMap;
        newMap = socket->getterDoc();*/
        curRoute = Train.route;
        if(!Train.route.isEmpty()) {
            qDebug() <<"ITERATORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"<<Train.iter;
            qDebug() <<"CURRENT FUCKING ROUTE"<< curRoute;
            int sourceEdgePoint = curRoute[Train.iter - 1];
            int destEdgePoint = curRoute[Train.iter];
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

            if(Train.position != (curLengh - destDiff)) {
                socket->sendMoveMessage(curEdgeIdx,curSpeed,Train.idx);
                //socket->sendTurnMessage();
                if((curLengh - destDiff) == curLengh) {
                    Train.position++;
                    this->player.setTrainPosition(Train);
                    this->player.getTrain(Train.idx).imageTrain->advancePosition(edgeVec[curEdge],curLengh,curSpeed,Train.position,this->animTimer);
                } else if((curLengh - destDiff) == 0){
                    Train.position--;
                    this->player.setTrainPosition(Train);
                    this->player.getTrain(Train.idx).imageTrain->advancePosition(edgeVec[curEdge],curLengh,curSpeed,Train.position,this->animTimer);
                }
            } else {
// Разбор стыка рёбер. Не оч красиво, но работает.
                if(Train.iter + 1 < curRoute.size()) {
                    if((curRoute[Train.iter] < curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] > 0)) {
                        Train.position = 0;
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] > curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] > 0)) {
                        Train.position = Table[std::min(curRoute[Train.iter], curRoute[Train.iter+1])][std::max(curRoute[Train.iter], curRoute[Train.iter+1])];
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] < curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] < 0)) {
                        Train.position = Table[std::min(curRoute[Train.iter], curRoute[Train.iter+1])][std::max(curRoute[Train.iter], curRoute[Train.iter+1])];
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] > curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] < 0)) {
                        Train.position = 0;
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    }
                } else {
                    if(curRoute[Train.iter] == pointsOfGraph.indexOf(player.getPlayerData().home_idx))
                    {
                        Train.route.clear();
                        Train.postsRoute.clear();
                        Train.iter = 1;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        this->player.setRoute(Train.idx, Train.route);
                        this->player.setPostsRoute(Train.idx, Train.postsRoute);

                    } else {
                        std::reverse(curRoute.begin(),curRoute.end());
                        player.setRoute(Train.idx,curRoute);
                        Train.iter = 1;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        Train.route = curRoute;
                        trainOneStep(Train);
                    }
                }
          }
	}
}

void GameLogic::trainsOneStep()
{
    this->animTimer = nullptr;
    this->animTimer = new QTimeLine(500);
    this->strategy->Moving(this->layer1, this->player);
    for(int i = 0; i < this->player.getPlayerTrains().size(); i++)
        trainOneStep(this->player.getPlayerTrains()[i]);
    this->animTimer->start();
    socket->SendMessage(MAP,{{"layer", 1}});
    this->layer1.Pars(socket->getterDoc());
    socket->sendTurnMessage();

}

bool GameLogic::CanTrainGo(train Train)
{
    for(int i = 0; i < layer1.getTrains().size(); i++)
    {
        //Ваня, запили функцию!!!!
    }
    return true;
}

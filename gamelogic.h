#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "mainwindow.h"
#include "edge.h"
//#include <stdlib.h>
#include <QObject>

class GameLogic : public QObject
{
    Q_OBJECT
public:
      GameLogic(SocketTest *socket, QVector<Edge *> &edgeVec,Train *imageTrain,Map0 &layer0, Map1 &layer1, Player &player);
      //void gameLoop(DijkstrasAlg *alg);
      void setTrainOnRoute(SocketTest *socket,train playerTrain,QVector<int> &pathToMarket,QVector<QVector<int>> &Table);
      void Alhoritm();
public slots:
      void trainOneStep();
private:
      Map0 layer0;
      Map1 layer1;
      Player player;

      SocketTest *socket;
      QVector<Edge *> edgeVec;
      Train *imageTrain;
      train playerTrain;
      int iter;
      QVector <QVector <int>> Table;
      QVector<int> curRoute;
      QVector<int> pointsOfGraph;
      QTimer* time;
      //int destDiff;
};
#endif // GAMELOGIC_H

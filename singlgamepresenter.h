#ifndef SINGLGAMEPRESENTER_H
#define SINGLGAMEPRESENTER_H

#include <QObject>
#include "mainwindow.h"
#include "mainwindowforsingleplay.h"
#include "graphwidget.h"

class SinglGamePresenter:public QObject
{
    Q_OBJECT
public:
    SinglGamePresenter(MainWindow *parent);
   // ~SinglGamePresenter();
public slots:
    void StartGame();
private:
    //MainWindowForSinglePlay *window;
};

#endif // SINGLGAMEPRESENTER_H

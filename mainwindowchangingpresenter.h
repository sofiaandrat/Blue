#ifndef MAINWINDOWCHANGINGPRESENTER_H
#define MAINWINDOWCHANGINGPRESENTER_H

#include "mainwindow.h"
#include "askselect.h"
#include "mainwindowforcreatemultigame.h"
#include "mainwindowforenterexistinggame.h"
#include "mainwindowforsingleplay.h"

class MainWindowChangingPresenter:public QObject
{
    Q_OBJECT
public:
    explicit MainWindowChangingPresenter(QDialog *parent);
    virtual ~MainWindowChangingPresenter();
public slots:
    void OpenSinglePlayerGameWindow();
    void OpenEnterToMultiplayerGameWindow();
    void OpenCreatingMultiplayerGameWindow();
};

#endif // MAINWINDOWCHANGINGPRESENTER_H

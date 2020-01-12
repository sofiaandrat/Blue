#ifndef SINGLEPLAYERPRESENTER_H
#define SINGLEPLAYERPRESENTER_H

#include <QObject>
#include "View/mainwindow.h"
#include "Model/isocketservice.h"
#include "Model/socketservice.h"
#include "View/askselect.h"
#include "View/mainwindowforsingleplay.h"

class SinglePlayerPresenter:public QObject
{
public:
    explicit SinglePlayerPresenter(MainWindow *parent, ISocketService * service);
    virtual ~SinglePlayerPresenter();
private:
    MainWindow *parent;
    ISocketService * service;
public slots:
    void LoginPush();
    void BackPush();
};

#endif // SINGLEPLAYERPRESENTER_H

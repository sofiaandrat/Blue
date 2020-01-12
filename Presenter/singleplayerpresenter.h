#ifndef SINGLEPLAYERPRESENTER_H
#define SINGLEPLAYERPRESENTER_H

#include <QObject>
#include "mainwindow.h"

class singleplayerpresenter:public QObject
{
public:
    explicit singleplayerpresenter(MainWindow *parent);
    virtual ~singleplayerpresenter();
private:
    MainWindow *parent;
};

#endif // SINGLEPLAYERPRESENTER_H

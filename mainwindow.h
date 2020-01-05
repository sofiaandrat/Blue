#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "sockettest.h"
//#include "graphwidget.h"
#include "structs.h"
#include "edge.h"
#include "train.h"
#include "node.h"
#include "dijkstrasalg.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    SocketTest *Socket;
    //Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

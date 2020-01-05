#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    game getGame();

protected:
    SocketTest *Socket;
    game Game;
    //Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

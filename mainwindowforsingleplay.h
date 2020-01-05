#ifndef MAINWINDOWFORSINGLEPLAY_H
#define MAINWINDOWFORSINGLEPLAY_H

//#include <QMainWindow>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForSinglePlay;
}
QT_END_NAMESPACE

class MainWindowForSinglePlay : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForSinglePlay(QWidget *parent = nullptr);
    ~MainWindowForSinglePlay();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindowForSinglePlay *ui;
};

#endif // MAINWINDOWFORSINGLEPLAY_H

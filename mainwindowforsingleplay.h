#ifndef MAINWINDOWFORSINGLEPLAY_H
#define MAINWINDOWFORSINGLEPLAY_H

//#include <QMainWindow>
#include "mainwindow.h"
#include "singlgamepresenter.h"
#include "askselect.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForSinglePlay;
}
QT_END_NAMESPACE

class MainWindowForSinglePlay : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForSinglePlay(QMainWindow *parent = nullptr);
    ~MainWindowForSinglePlay();
    QString getLoginText();
private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

private:
    Ui::MainWindowForSinglePlay *ui;
signals:
    void StartGame();
};

#endif // MAINWINDOWFORSINGLEPLAY_H

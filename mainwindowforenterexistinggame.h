#ifndef MAINWINDOWFORENTEREXISTINGGAME_H
#define MAINWINDOWFORENTEREXISTINGGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "structs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForEnterExistingGame;
}
QT_END_NAMESPACE

class MainWindowForEnterExistingGame : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForEnterExistingGame(QWidget *parent = nullptr);
    ~MainWindowForEnterExistingGame();

private slots:
    void on_refresh_clicked();

    void on_login_clicked();

private:
    Ui::MainWindowForEnterExistingGame *ui;
    QVector <game> gameList;
};

#endif // MAINWINDOWFORENTEREXISTINGGAME_H

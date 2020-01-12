#ifndef MAINWINDOWFORENTEREXISTINGGAME_H
#define MAINWINDOWFORENTEREXISTINGGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "Model/structs.h"
#include "askselect.h"

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
    QJsonObject getLoginData() override;
signals:
   // void BackPush() override;

private slots:
    void on_refresh_clicked();

    void on_login_clicked();

    void on_back_clicked();

private:
    Ui::MainWindowForEnterExistingGame *ui;
    QVector <game> gameList;
};

#endif // MAINWINDOWFORENTEREXISTINGGAME_H

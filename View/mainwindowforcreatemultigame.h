#ifndef MAINWINDOWFORCREATEMULTIGAME_H
#define MAINWINDOWFORCREATEMULTIGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "askselect.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForCreateMultigame;
}
QT_END_NAMESPACE

class MainWindowForCreateMultigame : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForCreateMultigame(QWidget *parent = nullptr);
    ~MainWindowForCreateMultigame() override;
    QJsonObject getLoginData() override;
    game * getGame() override;

private slots:
    void on_loginButton_clicked();
    void on_back_clicked();

private:
    Ui::MainWindowForCreateMultigame *ui;

};

#endif // MAINWINDOWFORCREATEMULTIGAME_H

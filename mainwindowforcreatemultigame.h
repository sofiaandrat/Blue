#ifndef MAINWINDOWFORCREATEMULTIGAME_H
#define MAINWINDOWFORCREATEMULTIGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "askselect.h"

namespace Ui {
class MainWindowForCreateMultigame;
}

class MainWindowForCreateMultigame : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForCreateMultigame(QWidget *parent = nullptr);
    ~MainWindowForCreateMultigame() override;

private slots:
    void on_loginButton_clicked();

    void on_back_clicked();

private:
    Ui::MainWindowForCreateMultigame *ui;

};

#endif // MAINWINDOWFORCREATEMULTIGAME_H

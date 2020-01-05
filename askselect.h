#ifndef ASKSELECT_H
#define ASKSELECT_H

#include <QDialog>
#include "mainwindow.h"
#include "mainwindowforsingleplay.h"
#include "mainwindowforcreatemultigame.h"
#include "mainwindowforenterexistinggame.h"

namespace Ui {
class AskSelect;
}

class AskSelect : public QDialog
{
    Q_OBJECT

public:
    explicit AskSelect(QWidget *parent = nullptr);
    ~AskSelect();
    void setMainWindow(MainWindow *window);

private slots:
    void on_single_clicked();

    void on_createMultiplayer_clicked();

    void on_enterMultiplayer_clicked();

private:
    Ui::AskSelect *ui;
    MainWindow *window;
};

#endif // ASKSELECT_H

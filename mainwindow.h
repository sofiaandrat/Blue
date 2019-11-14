#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>
#include <QMessageBox>
=======
>>>>>>> First commit

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;

    QString globpath;
    QFile file;


private slots:
    void on_actionOpen_json_file_triggered();
=======
private slots:
    void on_pushButton_clicked();
>>>>>>> First commit

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

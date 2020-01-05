#include "askselect.h"
#include "sockettest.h"
#include <QApplication>
#include <QCoreApplication>
#include "QDialog"
#include "mainwindowforsingleplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AskSelect askSelect;
    askSelect.show();
    MainWindow window;
    askSelect.setMainWindow(&window);
    return a.exec();
}

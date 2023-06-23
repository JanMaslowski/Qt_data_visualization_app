#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #FEEEE7;");
    w.show();
    return a.exec();
}

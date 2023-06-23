#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTranslator translator;
    //QStringList languages;
    //translator.load(":/translations/english.qm");
    //a.installTranslator(&translator);
    MainWindow w;
    w.setStyleSheet("background-color: #FEEEE7;");
    w.show();
    return a.exec();
}

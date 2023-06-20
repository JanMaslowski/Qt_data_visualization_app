#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QObject::tr("TO jest test");
    a.installTranslator(&translator);
    MainWindow w;
    w.setStyleSheet("background-color: #FEEEE7;");
    w.show();
    return a.exec();
}

#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "deviceconnection.h"
#include <QTimer>
#include<QTime>
#include <QElapsedTimer>
#include <QDialog>
#include <QMainWindow>
#include <QSerialPort>
#include <QVector>
#include<QTranslator>

namespace Ui
{
    class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

    public:

        explicit secondwindow(QWidget *parent = nullptr);
        ~secondwindow();
        void addDataToPlots(Data sensorData,int time);
        void clearData(); //uzywane

    signals:

        void clicked(); //uzywane

    private slots:

        void handleClicked(); //uzywane

    private:

        Ui::secondwindow *ui;
        void changeEvent(QEvent *event) override;
};

#endif // SECONDWINDOW_H

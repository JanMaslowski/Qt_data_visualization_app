#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "deviceconnection.h"
#include <QElapsedTimer>
#include <QDialog>
#include <QMainWindow>
#include <QSerialPort>
#include <QVector>
#include <QTimer>
#include<QTime>

namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();
    void transferToVector(Data sensorData,int time);
    void clearData();

signals:
    void clicked();

private slots:
 void handleClicked();

private:

    Ui::secondwindow *ui;
    QVector<double> Vx, Vy;
    void changeEvent(QEvent *event) override;
};

#endif // SECONDWINDOW_H

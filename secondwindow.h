#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H


#include <QDialog>
#include <QMainWindow>
#include <QSerialPort>
#include <QVector>

namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();


private slots:


private:
    Ui::secondwindow *ui;
    QVector<double> Vx, Vy;
};

#endif // SECONDWINDOW_H

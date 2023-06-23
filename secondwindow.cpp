#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "deviceconnection.h"


QCPTextElement *tytulTemp;
QCPTextElement *tytulHum;
QCPTextElement *tytulLux;

secondwindow::secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondwindow)
{

    QPen pen;
    pen.setWidth(2);
    ui->setupUi(this);
    this->setWindowTitle("Wykresy");
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &secondwindow::clearData);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &secondwindow::handleClicked);



    ui->plot_1->addGraph();
    ui->plot_1->graph()->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_1->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
    ui->plot_1->yAxis->setLabel(QApplication::translate("secondwindow","Temperatura [°C]"));
    ui->plot_1->xAxis->setRange(0,100);
    ui->plot_1->yAxis->setRange(20,30);
    ui->plot_1->graph()->setPen(pen);
    ui->plot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
    ui->plot_1->plotLayout()->insertRow(0);
    ui->plot_1->plotLayout()->addElement(0,0,tytulTemp=new QCPTextElement(ui->plot_1,"TEMPERATURA"));
    ui->plot_1->setBackground(QColor(200, 200, 200, 0));

    ui->plot_2->addGraph();
    ui->plot_2->graph()->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_2->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
    ui->plot_2->yAxis->setLabel(QApplication::translate("secondwindow","Wilgotność [%]"));
    ui->plot_2->xAxis->setRange(0,100);
    ui->plot_2->yAxis->setRange(20,80);
    ui->plot_2->graph()->setPen(pen);
    ui->plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
    ui->plot_2->plotLayout()->insertRow(0);
    ui->plot_2->plotLayout()->addElement(0,0,tytulHum=new QCPTextElement(ui->plot_2,"WILGOTNOŚĆ"));
    ui->plot_2->setBackground(QColor(200, 200, 200, 0));

    ui->plot_3->addGraph();
    ui->plot_3->graph()->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_3->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
    ui->plot_3->yAxis->setLabel(tr("CO2 [PPM]"));
    ui->plot_3->xAxis->setRange(0,100);
    ui->plot_3->yAxis->setRange(400,2000);
    ui->plot_3->graph()->setPen(pen);
    ui->plot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
    ui->plot_3->plotLayout()->insertRow(0);
    ui->plot_3->plotLayout()->addElement(0,0, new QCPTextElement(ui->plot_3,"CO2"));
    ui->plot_3->setBackground(QColor(200, 200, 200, 0));

    ui->plot_4->addGraph();
    ui->plot_4->graph()->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_4->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
    ui->plot_4->yAxis->setLabel( QApplication::translate("secondwindow","Naświetlenie [lx]"));
    ui->plot_4->xAxis->setRange(0,100);
    ui->plot_4->yAxis->setRange(300,2000);
    ui->plot_4->graph()->setPen(pen);
    ui->plot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
    ui->plot_4->plotLayout()->insertRow(0);
    ui->plot_4->plotLayout()->addElement(0,0,tytulLux=new QCPTextElement(ui->plot_4,"NASŁONECZNIENIE"));
    ui->plot_4->setBackground(QColor(200, 200, 200, 0));

    ui->plot_1->replot();
    ui->plot_1->update();
    ui->plot_2->replot();
    ui->plot_2->update();
    ui->plot_3->replot();
    ui->plot_3->update();
    ui->plot_4->replot();
    ui->plot_4->update();
}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::addDataToPlots(Data sensorData, int time)
{
    ui->plot_1->graph()->addData((double)time, (double)sensorData.temp);
    ui->plot_2->graph()->addData((double)time, (double)sensorData.hum);
    ui->plot_3->graph()->addData((double)time, (double)sensorData.CO2);
    ui->plot_4->graph()->addData((double)time, (double)sensorData.lux);
    ui->plot_1->graph()->rescaleAxes(true);
    ui->plot_1->update();
    ui->plot_1->replot();
    ui->plot_2->graph()->rescaleAxes(true);
    ui->plot_2->update();
    ui->plot_2->replot();ui->plot_2->yAxis->setLabel(QApplication::translate("secondwindow","Wilgotność [%]"));
    ui->plot_3->graph()->rescaleAxes(true);
    ui->plot_3->update();
    ui->plot_3->replot();
    ui->plot_4->graph()->rescaleAxes(true);
    ui->plot_4->update();
    ui->plot_4->replot();
}

void secondwindow::clearData()
{

    ui->plot_1->graph()->data()->clear();
    ui->plot_2->graph()->data()->clear();
    ui->plot_3->graph()->data()->clear();
    ui->plot_4->graph()->data()->clear();
    ui->plot_1->replot();
    ui->plot_2->replot();
    ui->plot_3->replot();
    ui->plot_4->replot();
}
void secondwindow::handleClicked()
{
    emit clicked();
}

void secondwindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        tytulTemp->setText(QApplication::translate("secondwindow","TEMPERATURA"));
        tytulHum->setText(QApplication::translate("secondwindow","WILGOTNOŚĆ"));
        tytulLux->setText(QApplication::translate("secondwindow","NASŁONECZNIENIE"));
        ui->plot_1->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
        ui->plot_2->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
        ui->plot_3->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
        ui->plot_4->xAxis->setLabel( QApplication::translate("secondwindow","Czas [s]"));
        ui->plot_1->yAxis->setLabel(QApplication::translate("secondwindow","Temperatura [°C]"));
        ui->plot_2->yAxis->setLabel(QApplication::translate("secondwindow","Wilgotność [%]"));
        ui->plot_4->yAxis->setLabel( QApplication::translate("secondwindow","Naświetlenie [lx]"));
        return;
    }
    QDialog::changeEvent(event);
}

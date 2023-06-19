#include "secondwindow.h"
#include "ui_secondwindow.h"


secondwindow::secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    ui->plot_1->addGraph();
    ui->plot_1->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_1->xAxis->setLabel("X");
    ui->plot_1->yAxis->setLabel("Y");
    ui->plot_1->xAxis->setRange(0,10);
    ui->plot_1->yAxis->setRange(20,30);

    ui->plot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    QVector<double> x={1,2,3,4,5},y={24,25,24.5,25,25};
    ui->plot_1->graph()->setData(x,y);
    //ui->plot_1->rescaleAxes();
    ui->plot_1->replot();
    ui->plot_1->update();
}
secondwindow::~secondwindow()
{
    delete ui;
}

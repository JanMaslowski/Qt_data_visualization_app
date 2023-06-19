#include "mainwindow.h"
#include "secondwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QChar>
#include <vector>
#include "deviceconnection.h"
#include <unistd.h>
#include <QPixmap>
#include <cmath>




Data sensorData{0,0,0,0,0,0};
/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //int w = ui->label_pic_CO2->width();
    //int h = ui->label_pic_CO2->height();
    //qDebug()<<h;
    //QPixmap CO2pix(":/resource/img/1.png");

    //ui->label_pic_CO2->setPixmap(CO2pix.scaled(150,150,Qt::KeepAspectRatioByExpanding));
    //displayImage(2);

    arduino =new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;


bool arduino_is_available = false;
QString arduino_uno_port_name;

//  For each available serial port
foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
{
    //  check if the serialport has both a product identifier and a vendor identifier
    if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
        //  check if the product ID and the vendor ID match those of the arduino uno
        if((serialPortInfo.productIdentifier() == arduino_nano_every_product_id)
                && (serialPortInfo.vendorIdentifier() == arduino_nano_every_vendor_id)){
            arduino_is_available = true; //    arduino uno is available on this port
            arduino_uno_port_name = serialPortInfo.portName();
        }
    }
}

/*
 *  Open and configure the arduino port if available
 */
if (arduino_is_available){
    QPixmap StatusPix(":/resource_diff/img_diff/status.png");
    ui->label_status->setPixmap(StatusPix.scaled(15,15,Qt::KeepAspectRatioByExpanding));
    ui->label_status_text->setText("Urządzenie podłączone");

    qDebug() << "Found the arduino port...\n";
    arduino->setPortName(arduino_uno_port_name);
    arduino->open(QSerialPort::ReadOnly);
    arduino->setBaudRate(QSerialPort::Baud19200);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(updateTemperature()));


}
else{
    qDebug() << "Couldn't find the correct port for the arduino.\n";
    QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    QPixmap statusnPix(":/resource_diff/img_diff/statusN.png");
    ui->label_status->setPixmap(statusnPix.scaled(15,15,Qt::KeepAspectRatioByExpanding));
    ui->label_status_text->setText("Urządzenie niepodłączone");
}

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTemperature()
{
    deviceconnection device;

    sensorData = device.reciveData(*arduino, sensorData);
    ui->lcd_temp->display(beautyfi(QString::number(sensorData.temp),1));
    displayImage("label_pic_temp",":/resource_temp/img2/",sensorData.temp,{16,26,1,21});
    ui->lcd_hum->display(beautyfi(QString::number(sensorData.hum),1));
    displayImage("label_pic_hum",":/resource_hum/img3/",sensorData.hum,{0,100,1,20});
    ui->lcd_CO2->display(beautyfi(QString::number(sensorData.CO2),2));
    displayImage("label_pic_CO2",":/resource_CO2/img/",sensorData.CO2,{400,2000,1,20});
    ui->lcd_lux->display(beautyfi(QString::number(sensorData.lux),2));
    displayImage("label_pic_lux",":/resource_lux/img4/",sensorData.lux,{0,1000,0,19});


}

void MainWindow::on_pushButton_clicked()
{
secondwindow graphwindow;
graphwindow.setModal(true);
graphwindow.exec();
}

QString MainWindow::beautyfi(QString text, int parameter)
{   QString mark;
    if (text.length()<5 && parameter ==1)
    {
        while(text.length()<5)
        {

            if(text.length()==2)
            {
                text+=".";
            }
            text+="0";
        }
    }
    if (text.length()<5 && parameter ==2)
    {
        while(text.length()<5)
        {

            if(text.length()==3)
            {
                text+=" ";
            }
            text=" "+text;
        }
    }

    mark=text;
    return mark;
}

double MainWindow::mapValue(double value, double inputMin, double inputMax, double outputMin, double outputMax) {
    double mappedValue = outputMin + (value - inputMin) * (outputMax - outputMin) / (inputMax - inputMin);
    mappedValue = std::max(outputMin, std::min(outputMax, mappedValue));

    return mappedValue;
}

void MainWindow::displayImage(QString labelname, QString resource,int sensor_value, QVector<int>map)
{
    QString imagePath;
    // Determine the image path based on the value
    double doublemappedvalue=mapValue(sensor_value,map[0],map[1],map[2],map[3]);
    int intValue = static_cast<int>(std::round(doublemappedvalue));;
    qDebug()<<doublemappedvalue;
    qDebug()<<intValue;
    QString stringValue = QString::number(intValue);
    imagePath = resource+stringValue+".png";
    // Find the QLabel based on the provided label name
    QLabel* label = findChild<QLabel*>(labelname);
    if (label) {
        // Load the image and scale it to the QLabel size
        QPixmap pixmap(imagePath);
        //label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QPixmap scaledPixmap = pixmap.scaled(label->size(), Qt::KeepAspectRatio);
        // Set the scaled pixmap in the QLabel
        label->setPixmap(scaledPixmap);

    }
}


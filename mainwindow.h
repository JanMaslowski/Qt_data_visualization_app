#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secondwindow.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Klasa głównego okna aplikacji.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @file mainwindow.h
     * @brief MainWindow
     * Konstruktor klasy MainWindow.
     * @param parent Wskaźnik na obiekt rodzica.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow
     * Destruktor klasy MainWindow.
     */
    ~MainWindow();

    //void checkArduinoAvailability();

private slots:
    /**
     * @brief updateTemperature
     * Slot dla aktualizacji temperatury.
     */
    void updateTemperature();
    void updateGraphs();
    void cleartimer();
    void EnglishButton();
    void PolishButton();
   // void handleArduinoAvailability(bool available);



    /**
     * @brief on_pushButton_clicked
     * Slot dla obsługi kliknięcia przycisku.
     */
    void secondpushButtonclicked();


    QString beautyfi(QString text, int parameter );


    /**
     * @brief displayImage
     * Wyświetla obrazek.
     * @param labelname Nazwa etykiety.
     * @param resource Ścieżka do zasobu obrazka.
     * @param CO2_value Wartość CO2.
     * @param map Wektor mapy.
     */
    void displayImage(QString labelname, QString resource, int sensor_value, QVector<int> map);

    /**
     * @brief mapValue
     * Mapuje wartość z zakresu wejściowego na zakres wyjściowy.
     * @param value Wartość do zmapowania.
     * @param inputMin Dolny zakres wejściowy.
     * @param inputMax Górny zakres wejściowy.
     * @param outputMin Dolny zakres wyjściowy.
     * @param outputMax Górny zakres wyjściowy.
     * @return Zmapowana wartość.
     */
    double mapValue(double value, double inputMin, double inputMax, double outputMin, double outputMax);



signals:
    //void arduinoAvailability(bool available);




private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_nano_every_vendor_id=9025;
    static const quint16 arduino_nano_every_product_id=88;

    secondwindow *graphwindow;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
    QTimer *timer;
    QElapsedTimer elapsedTimer;

    virtual void changeEvent ( QEvent *event) override ;

};

#endif // MAINWINDOW_H

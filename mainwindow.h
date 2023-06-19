#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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

private slots:
    /**
     * @brief updateTemperature
     * Slot dla aktualizacji temperatury.
     */
    void updateTemperature();

    /**
     * @brief on_pushButton_clicked
     * Slot dla obsługi kliknięcia przycisku.
     */
    void on_pushButton_clicked();


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

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_nano_every_vendor_id=9025;
    static const quint16 arduino_nano_every_product_id=88;

    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
};

#endif // MAINWINDOW_H

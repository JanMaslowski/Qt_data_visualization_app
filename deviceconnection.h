#ifndef DEVICECONNECTION_H
#define DEVICECONNECTION_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QChar>
#include <vector>
#include<QTranslator>

/*!
 * \brief Struktura Data
 *
 * Struktura Data zawiera zmienne odbierane z urządzenia.
 */
struct Data
{
    float temp = 0; ///< Temperatura.
    float hum = 0; ///< Wilgotność.
    float CO2 = 0; ///< Poziom CO2.
    float tVOC = 0; ///< Poziom TVOC.
    float lux = 0; ///< Poziom oświetlenia.
    float checkSum = 0; ///< Suma kontrolna.
};

/*!
 * \brief The deviceconnection class
 *
 * Klasa odpowiedzialna za odbieranie danych z urządzenia.
 */
class deviceconnection
{
    public:
        /**
         * @brief deviceconnection
         * Konstruktor klasy deviceconnection.
         */
        deviceconnection();

        /**
         * @brief reciveData
         * Odbiera dane z urządzenia.
         * @param arduino Obiekt klasy QSerialPort reprezentujący połączenie z urządzeniem.
         * @param sensorData Dane z czujnika.
         * @return Zaktualizowane dane z czujnika.
         */
        Data reciveData(QSerialPort& arduino, Data sensorData);
};

#endif // DEVICECONNECTION_H

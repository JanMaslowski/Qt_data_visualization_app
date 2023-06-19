#include "deviceconnection.h"

deviceconnection::deviceconnection()
{

}
Data deviceconnection::reciveData(QSerialPort& arduino, Data sensorData)
{
    std::vector<float> buffer;
    QList<float> floatList;

    if (arduino.canReadLine()){
            QByteArray data = arduino.readLine();
            qDebug() << data;

            int startIndex = 1;
            for (int i = 1; i < data.size(); i++) {
                //qDebug() << i;
                if (data[i] == ',' || data[i] == ']') {

                    QString floatStr = data.mid(startIndex, i - startIndex);
                    //qDebug() << floatStr;
                    floatList.append(floatStr.toFloat());
                    startIndex = i + 1;
                }
            }
            float checkSum=0;
            for(int i=0;i<5;i++)
            {
              checkSum+=floatList[i];
            }
            if(checkSum-floatList[5]<0.02||checkSum-floatList[5]>-0.02)
            {
             qDebug() << "Dane się zgadzaja)";

            }
            else
            {
                qDebug()<< checkSum;
                qDebug()<< floatList[5];
            }

        sensorData.temp=floatList[0];
        sensorData.hum=floatList[1];
        sensorData.CO2=floatList[2];
        sensorData.tVOC=floatList[3];
        sensorData.lux=floatList[4];

    }
return sensorData;
}

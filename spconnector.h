#ifndef SPCONNECTOR_H
#define SPCONNECTOR_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include "pulsationhandler.h"

class SPConnector : public QObject
{
    Q_OBJECT
public:
    explicit SPConnector(QObject *parent = 0);
    ~SPConnector();

    int baudRate() const;
    void setBaudRate(int baudRate);

    QString portName() const;
    void setPortName(const QString &portName);
    void autoSetPortName();

    bool isOpen() const;

    virtual bool open();
    virtual void close();
    virtual bool clear();

private:
    QString m_portName;
    int m_baudRate;
    QSerialPort *m_serialPort;
    QByteArray tempBuffer;

    void validateAndSendData(QByteArray data);

signals:
    void sendData(QStringList dataList);
public slots:
    void readData();
};

#endif // SPCONNECTOR_H

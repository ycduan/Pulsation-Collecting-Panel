#include "spconnector.h"

SPConnector::SPConnector(QObject *parent) : QObject(parent)
{
    m_serialPort = new QSerialPort();
    m_portName = "com3";
    m_baudRate = QSerialPort::Baud115200;
    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(this, SIGNAL(sendData(QStringList)), parent, SLOT(readData(QStringList)));
}

SPConnector::~SPConnector()
{
    delete m_serialPort;
}

int SPConnector::baudRate() const
{
    return m_baudRate;
}

void SPConnector::setBaudRate(int baudRate)
{
    m_baudRate = baudRate;
}

QString SPConnector::portName() const
{
    return m_portName;
}

void SPConnector::setPortName(const QString &portName)
{
    m_portName = portName;
}

void SPConnector::autoSetPortName()
{
    foreach (QSerialPortInfo portInfo, QSerialPortInfo::availablePorts()) {
//        if(portInfo.description() == "USB-SERIAL CH340") {
        if(portInfo.description() == "Arduino Uno") {
            m_portName = portInfo.portName();
            qDebug() << portInfo.portName()+ "-"+ portInfo.description() + " was found.";
        }
    }
}

bool SPConnector::isOpen() const
{
    return m_serialPort->isOpen();
}

bool SPConnector::open()
{
    if(m_serialPort->isOpen()) {
        return true;
    }
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(m_baudRate);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort->setReadBufferSize(1024);
    if(m_serialPort->open(QSerialPort::ReadWrite)) {
        qDebug() << "open successfully!";
        return true;
    } else {
        qDebug() << "open unsuccessfully! " + m_serialPort->errorString();
        return false;
    }
}

void SPConnector::close()
{
    if(m_serialPort->isOpen()) {
        m_serialPort->close();
    }
}

bool SPConnector::clear()
{
    if(m_serialPort->isOpen()) {
        m_serialPort->clear();
        this->clear();
        return this->open();
    }
    return false;
}

void SPConnector::validateAndSendData(QByteArray data)
{
    QStringList dataList = QString(data).split(", ");
    if(dataList.size() == 4) {
        emit sendData(dataList);
    } else {
        qDebug() << dataList.size();
    }
}

void SPConnector::readData()
{
    QByteArray temp = m_serialPort->readAll();
    if(!temp.isEmpty()) {
        tempBuffer.append(temp);
        if(tempBuffer.contains("#")) {
            QByteArray data = tempBuffer.split('#').at(0);
            tempBuffer = tempBuffer.right(tempBuffer.size() - tempBuffer.indexOf("#") - 1);
            validateAndSendData(data);
        }
    }
}

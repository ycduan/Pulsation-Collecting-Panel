#include "pulsationhandler.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

PulsationHandler::PulsationHandler(QObject *parent) : QObject(parent)
{
    pulsationList = new QLinkedList<QStringList>;
    status = false;
    index = 0;
    overall = 60 * 1000;
    interval = 20;
    listSize = overall / interval;
    connect(this, SIGNAL(collectCompleted()), parent, SLOT(stopSubmit()));
    connect(this, SIGNAL(noticeProgressBar(int)), parent, SLOT(setProgressBar(int)));
}

PulsationHandler::~PulsationHandler()
{
    delete pulsationList;
}

void PulsationHandler::resetPulList()
{
    delete pulsationList;
    pulsationList = new QLinkedList<QStringList>;
    index = 0;
}

void PulsationHandler::collectData(QStringList dataList)
{
    if(index < listSize) {
        pulsationList->append(dataList);
        index ++;
        emit noticeProgressBar(index * 100 / listSize);
        qDebug() << index;
    } else {
        this->savePulsation();
        emit collectCompleted();
    }
}

void PulsationHandler::savePulsation()
{
    QDateTime time = QDateTime::currentDateTime();
    QString filename = "data/" + time.toString("yyyyMMddhhmmss") + ".csv";
    qDebug() << filename;
    QFile file(filename);
    if(file.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << this->name << ",\r\n" << this->gender << ",\r\n" << this->age << ",\r\n" << this->description << ",\r\n";
        QStringList sl;
        bool ok;
        double base = pulsationList->first().at(3).toDouble();
        foreach (sl, *pulsationList) {

            out << sl.at(0) << ", " << sl.at(1) << ", " << sl.at(2) << ", " << sl.at(3) << ", " << sl.at(3).toDouble() - base << "\r\n";
        }
    }
    this->resetPulList();
}

void PulsationHandler::setSubjectInfo(QString name, QString gender, QString age, QString description)
{
    this->name = name;
    this->gender = gender;
    this->age = age;
    this->description = description;
}


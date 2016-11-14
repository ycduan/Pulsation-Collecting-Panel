#ifndef INFOHANDLER_H
#define INFOHANDLER_H

#include <QObject>
#include <QFile>
#include <qdebug.h>
#include <qdatastream.h>
#include <QLinkedList>

class PulsationHandler : public QObject
{
    Q_OBJECT
public:
    explicit PulsationHandler(QObject *parent = 0);
    ~PulsationHandler();

    void resetPulList();
    void collectData(QStringList dataList);
    void savePulsation();
    void setSubjectInfo(QString name, QString gender, QString age, QString description);

private:
    bool status;
    int index;
    int overall;
    int interval;
    int listSize;
    QLinkedList<QStringList> *pulsationList;

    QString name;
    QString gender;
    QString age;
    QString description;

signals:
    void collectCompleted();
    void noticeProgressBar(int num);

public slots:
};

#endif // INFOHANDLER_H

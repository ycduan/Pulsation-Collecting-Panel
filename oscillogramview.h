#ifndef OSCILLOGRAMVIEW_H
#define OSCILLOGRAMVIEW_H

#include <QWidget>
#include <QLinkedList>

namespace Ui {
class OscillogramView;
}

class OscillogramView : public QWidget
{
    Q_OBJECT

public:
    explicit OscillogramView(QWidget *parent = 0);
    ~OscillogramView();

private:
    Ui::OscillogramView *ui;
    bool status;
    int index;
    int listSize;
    QVector<double> dataVector1;
    QVector<double> dataVector2;
    QVector<double> dataVector3;
    QVector<double> timeVector;

public slots:
    void replot(QStringList dataList);
};

#endif // OSCILLOGRAMVIEW_H

#include "oscillogramview.h"
#include "ui_oscillogramview.h"
#include <QTime>
#include <ctime>

OscillogramView::OscillogramView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OscillogramView)
{
    ui->setupUi(this);
    index = 0;
    listSize = 500;

    ui->oscView1->addGraph();
    ui->oscView2->addGraph();
    ui->oscView3->addGraph();

    ui->oscView1->xAxis->setRange(0, 1000);
    ui->oscView1->yAxis->setRange(0, 5);
    ui->oscView2->xAxis->setRange(0, 1000);
    ui->oscView2->yAxis->setRange(0, 5);
    ui->oscView3->xAxis->setRange(0, 1000);
    ui->oscView3->yAxis->setRange(0, 5);
}

OscillogramView::~OscillogramView()
{
    delete ui;
}

void OscillogramView::replot(QStringList dataList)
{
    if(index < listSize) {
        dataVector1.append(dataList.at(0).toDouble());
        dataVector2.append(dataList.at(1).toDouble());
        dataVector3.append(dataList.at(2).toDouble());
        timeVector.append(2 * index);
        index ++;
    } else {
        dataVector1.removeFirst();
        dataVector1.append(dataList.at(0).toDouble());
        dataVector2.removeFirst();
        dataVector2.append(dataList.at(1).toDouble());
        dataVector3.removeFirst();
        dataVector3.append(dataList.at(2).toDouble());
    }
    ui->oscView1->graph(0)->setData(timeVector, dataVector1);
    ui->oscView2->graph(0)->setData(timeVector, dataVector2);
    ui->oscView3->graph(0)->setData(timeVector, dataVector3);
    ui->oscView1->replot();
    ui->oscView2->replot();
    ui->oscView3->replot();
}

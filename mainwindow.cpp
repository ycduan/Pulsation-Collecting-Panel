#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    spc = new SPConnector(this);
    pulsationHdl = new PulsationHandler(this);
    ui->setupUi(this);

    this->initParam();
}

MainWindow::~MainWindow()
{
    delete spc;
    delete pulsationHdl;
    delete ui;
}

void MainWindow::readData(QStringList dataList)
{
    counter ++;
    if(counter > 19) {
        ui->pulsation1->setText(dataList[0]);
        ui->pulsation2->setText(dataList[1]);
        ui->pulsation3->setText(dataList[2]);
        counter = 0;
    }
    if(submitStatus) {
        pulsationHdl->collectData(dataList);
    }
}

void MainWindow::stopSubmit()
{
    this->submitStatus = false;
    ui->submitBtn->setEnabled(true);
    ui->resetBtn->setEnabled(true);
    ui->viewBtn->setEnabled(true);
    QMessageBox::warning(this, "Message", "Saving file is succeed!", QMessageBox::Yes);
}

void MainWindow::setProgressBar(int num)
{
    ui->progressBar->setValue(num);
}

void MainWindow::on_openBtn_clicked()
{
    spc->autoSetPortName();
    if(spc->open()) {
        this->openStatusWidget();
    } else {
        QMessageBox::warning(NULL, "Message", "COM opening is failed!", QMessageBox::Yes);
    }
}

void MainWindow::on_closeBtn_clicked()
{
    spc->close();
    this->initParam();
    pulsationHdl->resetPulList();
    this->closeStatusWidget();
}

void MainWindow::on_resetBtn_clicked()
{
    ui->nameLineEdit->clear();
    ui->ageLineEdit->clear();
    ui->DescTextEdit->clear();
    ui->progressBar->setValue(0);
}

void MainWindow::on_submitBtn_clicked()
{
    this->submitStatusWidget();
    pulsationHdl->setSubjectInfo(ui->nameLineEdit->text(), ui->genderComboBox->currentText(), ui->ageLineEdit->text(), ui->DescTextEdit->toPlainText());
    this->submitStatus = true;
}

void MainWindow::openStatusWidget()
{
    ui->closeBtn->setEnabled(true);
    ui->submitBtn->setEnabled(true);
    ui->resetBtn->setEnabled(true);
    ui->openBtn->setEnabled(false);
    ui->viewBtn->setEnabled(true);
}

void MainWindow::closeStatusWidget()
{
    ui->closeBtn->setEnabled(false);
    ui->submitBtn->setEnabled(false);
    ui->viewBtn->setEnabled(false);
    ui->pulsation1->clear();
    ui->pulsation2->clear();
    ui->pulsation3->clear();
    ui->openBtn->setEnabled(true);
    ui->progressBar->setValue(0);
}

void MainWindow::submitStatusWidget()
{
    ui->viewBtn->setEnabled(false);
    ui->submitBtn->setEnabled(false);
    ui->resetBtn->setEnabled(false);
    ui->progressBar->setValue(0);
}

void MainWindow::initParam()
{
    submitStatus = false;
    counter = 20;
}

void MainWindow::on_viewBtn_clicked()
{
    ov = new OscillogramView();
    ov->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(this->spc, SIGNAL(sendData(QStringList)), this->ov, SLOT(replot(QStringList)));
    ov->show();
}

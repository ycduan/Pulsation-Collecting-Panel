#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <spconnector.h>
#include <pulsationhandler.h>
#include <oscillogramview.h>
#include <mutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SPConnector *spc;
    PulsationHandler *pulsationHdl;
    OscillogramView *ov;

private slots:
    void readData(QStringList dataList);
    void stopSubmit();
    void setProgressBar(int num);
    void on_openBtn_clicked();
    void on_closeBtn_clicked();
    void on_resetBtn_clicked();
    void on_submitBtn_clicked();
    void on_viewBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool submitStatus;
    int counter;

    void openStatusWidget();
    void closeStatusWidget();
    void submitStatusWidget();
    void initParam();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linker = new ble_linker();
    connect(linker, SIGNAL(deviceFound(QString, QString)),
            this, SLOT(newDevFound(QString, QString)));

    connect(linker, SIGNAL(sendNewResult(double)), this, SLOT(getNewResult(double)));

    currentResult = 0;
    max=0;
    initGraph();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initGraph() {
    ui->widget->addGraph();
}

void MainWindow::newDevFound(QString devName, QString address) {
    devices.append(devName);
    ui->textEdit->insertPlainText(devName+"\r");
    ui->textEdit->insertPlainText(address+"\r");
}

void MainWindow::on_pushButton_clicked()
{
    linker->startScanner();
}

void MainWindow::on_pushButton_2_clicked()
{
    linker->ledsOn();
}

void MainWindow::on_pushButton_3_clicked()
{
    linker->ledsOff();
}

void MainWindow::on_pushButton_4_clicked()
{
    linker->readLed();
}


void MainWindow::getNewResult(double newResult) {
    double temp = log(10240000/newResult-10000);
    if (newResult>max) {
        max = newResult;
    }
    adcResults.append(newResult);
    xCoords.append(currentResult);
    currentResult++;

    ui->widget->xAxis->setRange(0, currentResult);
    ui->widget->yAxis->setRange(0,max);
    ui->widget->graph(0)->setData(xCoords, adcResults);
    ui->widget->replot();

    if (ui->checkBox->isChecked()) {
        linker->readLed();
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    linker->readLed();
}

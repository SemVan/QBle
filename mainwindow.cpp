#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linker = new ble_linker();
    connect(linker, SIGNAL(deviceFound(QString)),
            this, SLOT(newDevFound(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newDevFound(QString devName) {
    devices.append(devName);
    ui->textEdit->setText(devName);
}

void MainWindow::on_pushButton_clicked()
{
    linker->startScanner();
}

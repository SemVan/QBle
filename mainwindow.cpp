#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linker = new ble_linker();
    connect(linker, SIGNAL(deviceFound(QString, QString)),
            this, SLOT(newDevFound(QString, QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
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

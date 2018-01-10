#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linker = new ble_linker();

    //connect(linker, SIGNAL(sendNewResult(double, int)), this, SLOT(getNewResult(double, int)));
    currentResult = 0;
    max=0;
    initGraph();

    //container = new DataContainer();
    //container->init(ui->widget, 0);
    for (int i=0; i<3; i++) {
        container.append(new DataContainer());
        container.at(i)->init(ui->widget, i);
    }


}

MainWindow::~MainWindow()
{
    for (int i=0; i<container.length(); i++) {
        delete container.at(i);
    }
    delete ui;
}


void MainWindow::initGraph() {

    displays.append(ui->lcdNumber);
    displays.append(ui->lcdNumber_2);
    displays.append(ui->lcdNumber_3);

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(255,0,0)));
    ui->widget->graph(0)->setName("Sensor 1");

    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(QColor(0,255,0)));
    ui->widget->graph(1)->setName("Sensor 2");

    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(QColor(0,0,255)));
    ui->widget->graph(2)->setName("Sensor 3");

    ui->widget->legend->setVisible(true);

    ui->lcdNumber->setPalette(QColor(255,0,0));
    ui->lcdNumber_2->setPalette(QColor(0,255,0));
    ui->lcdNumber_3->setPalette(QColor(0,0,255));
}


void MainWindow::getNewResult(double newResult, int num) {
    container.at(num)->addNew(newResult);
    container.at(num)->plotGraph();
    displays.at(num)->display(newResult);
}

void MainWindow::on_pushButton_7_clicked()
{
    server = new UDPServer();
    connect(server, SIGNAL(sendDataToTheWorld(double, int)), this, SLOT(getNewResult(double, int)));
    connect(server,SIGNAL(connectionEstablished()), this, SLOT(deviceConnected()));
}


void MainWindow::deviceConnected() {

    ui->pushButton_7->setStyleSheet("background-color: rgb(0, 255, 0, 80)");
    return;
}


void MainWindow::writeLog(QString fileToSaveTo) {
    QFile tableOut(fileToSaveTo);
    QString title= QString("Error");
    QString mes=QString("Can not open file");


        if(!tableOut.open(QIODevice::WriteOnly)) {
            qDebug() << "shit";
            QMessageBox::information(this,title,mes);
            return ;
        }

//    QString yo;
//    QTextStream out(&tableOut);

//    for(int i=0;i<m;i++) {
//            yo=ui->tableWidget->horizontalHeaderItem(i)->text();
//            yo.replace(","," ");
//            out<<yo<<",";
//        }

//    out<<"\n";

//    for(int j=0;j<n;j++) {
//        for (int i=0;i<m;i++) {
//            yo=ui->tableWidget->item(j,i)->text();
//            out<<yo<<",";
//        }
//        out<<"\n";
//    }
    tableOut.close();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //linker = new ble_linker();

    //connect(linker, SIGNAL(sendNewResult(double, int)), this, SLOT(getNewResult(double, int)));
    currentResult = 0;
    max=0;
    initGraph();


    for (int i=0; i<5; i++) {
        container.append(new DataContainer());
        container.at(i)->init(ui->widget, i);
    }
    qDebug()<<"container length = "<<container.length();


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
    displays.append(ui->lcdNumber_4);
    displays.append(ui->lcdNumber_5);

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(255,0,0)));
    ui->widget->graph(0)->setName("Sensor 1");

    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(QColor(0,255,0)));
    ui->widget->graph(1)->setName("Sensor 2");

    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(QColor(0,0,255)));
    ui->widget->graph(2)->setName("Sensor 3");

    ui->widget->addGraph();
    ui->widget->graph(3)->setPen(QPen(QColor(255,0,255)));
    ui->widget->graph(3)->setName("Sensor 4");

    ui->widget->addGraph();
    ui->widget->graph(4)->setPen(QPen(QColor(0,255,255)));
    ui->widget->graph(4)->setName("Sensor 5");

    ui->widget->legend->setVisible(true);

    ui->lcdNumber->setPalette(QColor(255,0,0));
    ui->lcdNumber_2->setPalette(QColor(0,255,0));
    ui->lcdNumber_3->setPalette(QColor(0,0,255));
    ui->lcdNumber_4->setPalette(QColor(255,0,0));
    ui->lcdNumber_5->setPalette(QColor(0,255,0));

}


void MainWindow::getNewResult(double newResult, int num) {

    qDebug()<<"container num = "<<num;
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

void MainWindow::on_pushButton_clicked()
{
    QString directory=QApplication::applicationDirPath() + "//Data//";
    QString temp=QFileDialog::getSaveFileName(this, "Sabe to", directory);

    if (temp != "") {
        qDebug()<<"norm";
    }
}

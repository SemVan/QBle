#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ble_linker.h"
#include <qcustomplot.h>
#include "udpserver.h"
#include "datacontainer.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ble_linker *linker;
    QList<QString> devices;
    UDPServer *server;
    double max;
    QVector<DataContainer*> container;
    QVector<QLCDNumber*> displays;

    QVector<double> adcResults;
    QVector<double> xCoords;
    int currentResult;

    void initGraph();
    void writeLog(QString fileToSaveTo);
private slots:
    void getNewResult(double newResult, int num);
    void on_pushButton_7_clicked();
    void deviceConnected();
};

#endif // MAINWINDOW_H

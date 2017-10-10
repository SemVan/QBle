#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ble_linker.h"
#include <qcustomplot.h>


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
    double max;

    QVector<double> adcResults;
    QVector<double> xCoords;
    int currentResult;

    void initGraph();
private slots:
    void newDevFound(QString devName, QString address);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void getNewResult(double newResult);
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H

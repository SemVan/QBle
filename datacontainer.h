#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>
#include "qcustomplot.h"
class DataContainer : public QObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = 0);
    void init(QCustomPlot *graph, int number);
    void addNew(double newResult);
    void plotGraph();
private:
    QVector<double> data;
    QVector<double> time;
    QCustomPlot *plot;
    int graphNum;
    int currentNum;
    double min;
    double max;


signals:

public slots:
};

#endif // DATACONTAINER_H

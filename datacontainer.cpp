#include "datacontainer.h"

DataContainer::DataContainer(QObject *parent) : QObject(parent)
{

}

void DataContainer::init(QCustomPlot *graph, int number) {
    plot = graph;
    graphNum = number;
    currentNum = 0;
    min = 65535;
    max = 0;
    return;
}


void DataContainer::addNew(double newResult) {
    data.append(newResult);
    time.append((double)currentNum);
    currentNum++;

    if (newResult>max) {
        max = newResult;
    }
    if (newResult<min) {
        min = newResult;
    }
    return;
}


void DataContainer::plotGraph() {
    plot->xAxis->setRange(0, currentNum);
    plot->yAxis->setRange(max,min);
    plot->graph(graphNum)->setData(time, data);
    plot->replot();
}

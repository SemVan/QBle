#include "ble_linker.h"

#include <QDebug>

ble_linker::ble_linker(QObject *parent) : QObject(parent)
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->

    connect(discoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(discoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(deviceScanFinished()));

}

void ble_linker::deviceScanFinished() {
    int a;
    a++;
}

void ble_linker::startScanner() {
    discoveryAgent->start();
}

void ble_linker::addDevice(const QBluetoothDeviceInfo &info) {
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        if (info.name().contains("Project")) {
            createController(info);
            deviceFound(info.name(), info.address().toString());
        }
    }
}

void ble_linker::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error err) {
    QString str;
}


void ble_linker::connectionEstablished() {
    qDebug()<<"connection established\r";
    controller->discoverServices();
}

void ble_linker::addService(QBluetoothUuid uuid) {
    QString str;
    qDebug()<<"New service discovered";
    str = QString::number(uuid.data1, 16);
    qDebug()<<str;
    str = QString::number(uuid.data2, 16);
    qDebug()<<str;
    str = QString::number(uuid.data3, 16);
    qDebug()<<str;

}

void ble_linker::createController(QBluetoothDeviceInfo info) {
    qDebug()<<"device found. creating controller! trying to connect...\r";
    controller = new QLowEnergyController(info);
    connect(controller, SIGNAL(connected()), this, SLOT(connectionEstablished()));
    connect(controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(addService(QBluetoothUuid)));
    controller->connectToDevice();

}

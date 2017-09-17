#include "ble_linker.h"

#include <QDebug>
#include <QByteArray>

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
            qDebug()<<"Device found "+info.name();
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
    //qDebug()<<str;
    if (str=="f0001110") {
        qDebug()<<"LED service found";
        service = controller->createServiceObject(uuid);

        connect(service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)), this, SLOT(detailsDiscovered(QLowEnergyService::ServiceState)));

        service->discoverDetails();
    }

}

void ble_linker::detailsDiscovered(QLowEnergyService::ServiceState s) {
    QList<QLowEnergyCharacteristic> list = service->characteristics();


    for (int i=0; i<list.length(); i++) {
        QList<QLowEnergyDescriptor> scripts = list.at(i).descriptors();
        QByteArray value = list.at(i).value();
        QString serName = QString::number(list.at(i).uuid().data1, 16);
        qDebug() << "Characterictic name "+serName;
        qDebug() << "Value is "+QString::fromStdString(value.toStdString());
        service->writeCharacteristic(list.at(i), QByteArray("0000"));

    }
}

void ble_linker::createController(QBluetoothDeviceInfo info) {
    qDebug()<<"device found. creating controller. trying to connect...\r";
    controller = new QLowEnergyController(info);
    connect(controller, SIGNAL(connected()), this, SLOT(connectionEstablished()));
    connect(controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(addService(QBluetoothUuid)));
    controller->connectToDevice();

}

#ifndef BLE_LINKER_H
#define BLE_LINKER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothUuid>
#include <QLowEnergyService>

class ble_linker : public QObject
{
    Q_OBJECT
public:
    explicit ble_linker(QObject *parent = 0);
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    void startScanner();
    QLowEnergyController *controller;
    void createController(QBluetoothDeviceInfo info);
    QLowEnergyService *service;
signals:
    void deviceFound(QString deviceName, QString address);

public slots:
    void connectionEstablished();
    void deviceScanFinished();
    void addDevice(const QBluetoothDeviceInfo &info);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error err);
    void addService(QBluetoothUuid uuid);
    void detailsDiscovered(QLowEnergyService::ServiceState s);
};

#endif // BLE_LINKER_H

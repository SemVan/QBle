#ifndef BLE_LINKER_H
#define BLE_LINKER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QElapsedTimer>


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
    void ledsOn();
    void ledsOff();
    void readLed();

private:
    QElapsedTimer timer;
    QList<QLowEnergyCharacteristic> char_list;
signals:
    void deviceFound(QString deviceName, QString address);
    void sendNewResult(double newResult);

public slots:
    void connectionEstablished();
    void deviceScanFinished();
    void addDevice(const QBluetoothDeviceInfo &info);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error err);
    void addService(QBluetoothUuid uuid);
    void detailsDiscovered(QLowEnergyService::ServiceState s);
    void charReadSuck(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
};

#endif // BLE_LINKER_H

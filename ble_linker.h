#ifndef BLE_LINKER_H
#define BLE_LINKER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

class ble_linker : public QObject
{
    Q_OBJECT
public:
    explicit ble_linker(QObject *parent = 0);
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    void startScanner();

signals:
    void deviceFound(QString deviceName);

public slots:
    void deviceScanFinished();
    void addDevice(const QBluetoothDeviceInfo &info);
};

#endif // BLE_LINKER_H

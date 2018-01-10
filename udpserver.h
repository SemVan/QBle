
#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UDPServer : public QObject
{
    Q_OBJECT
public:
    explicit UDPServer(QObject *parent = 0);
    QUdpSocket *socket;

private:
    double parseData(QByteArray data);
    double fullMessageParser(QByteArray message);

signals:
    void sendDataToTheWorld(double temp, int num);
    void connectionEstablished();

public slots:
    void dataCame();

};

#endif // UDPSERVER_H

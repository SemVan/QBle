#include "udpserver.h"
#include "QDebug"
#include "QHostAddress"


UDPServer::UDPServer(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket();
    QHostAddress address("0.0.0.0");
    socket->bind(QHostAddress("0.0.0.0"), 5000);
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(dataCame()));
    qDebug()<<"server started";
}

void UDPServer::dataCame() {
    QByteArray answer;
    char array[20];
    QHostAddress *senderAddress = new QHostAddress;
    qint64 d = socket->readDatagram(array, 20, senderAddress);

    for (int i=0; i<d; i++) {
        answer.append(array[i]);
    }

    qDebug()<<QString(answer);


    if (QString(answer) == QString("hello")) {
        socket->writeDatagram(QByteArray::fromStdString("canyouhearme?"), *senderAddress, 5000);
    } else {
        if (QString(answer) == QString("imincalifornia")) {
            connectionEstablished();
        } else {
            if ((QString(answer) != QString("None"))) {
                qDebug()<<answer.length();
                fullMessageParser(answer);
            }
        }
    }
}

double UDPServer::fullMessageParser(QByteArray message) {
    message = message.mid(3,message.length()-3);
    if (message.length()==10) {
        for (int i=0; i<5; i++) {
            sendDataToTheWorld(parseData(message.mid(i*2, 2)), i);
        }
    }
}

double UDPServer::parseData(QByteArray data) {
    //data = data.mid(3,2);
    int h = (int)data.at(1);
    if (h < 0) {
        h = h+255;
    }
    int l = (int)data.at(0);
    if (l < 0) {
        l = l+255;
    }

    int Bytes = h << 8 | l;
    Bytes &= 0xFFFC; //Mask NVM bits not used in Temperature Result
    double temperature = (float) Bytes / 256;
    qDebug()<<temperature;

    return temperature;
}

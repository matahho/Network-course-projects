#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QQueue>
#include <iostream>

#include "packet.h"

class Port : public QObject
{
    Q_OBJECT
public:
    explicit Port(int maxq , QObject *parent = nullptr);
    void sendPacket(QSharedPointer<Packet> pack);
    void increasePacketsLifeSpan();

    bool isQueueFull() {return queue.size() == maxQueueSize;}

    QSharedPointer<Packet> dequeue(){return queue.dequeue();}

private:
    QQueue<QSharedPointer<Packet>> queue;
    int maxQueueSize;

public slots:
    void recievePacket(QSharedPointer<Packet> pack);
signals:
    void newPacketArrived(QSharedPointer<Packet> pack);
};





#endif // PORT_H

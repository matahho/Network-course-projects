#ifndef HOST_H
#define HOST_H

#include <QObject>
#include "port.h"
#include "Node.h"
#include "utility.hpp"
#include "packet.h"


class Host : public Node
{
    Q_OBJECT
public:
    explicit Host(IP ip ,
                  VersionOfIP v
                  , int _portQueueSize);


    void getIpFromDHCPServer();

    Port * getPort() {return port;}

    void handleIncomingPackets();

    QSharedPointer<Packet> createPacket(IP destination , QString data);
private:

    IP nearestRouter;

    Port * port;

public slots:
    void onClock(NetworkState ns) override;
    void sendPacketTo(QString destination);
};

#endif // HOST_H

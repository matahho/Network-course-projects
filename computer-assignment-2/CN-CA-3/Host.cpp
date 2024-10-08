// #include "Host.h"

// Host::Host(IP theIP
//            ,VersionOfIP v ,
//            int thePortQueueSize
//            )
//         :Node(theIP , v , thePortQueueSize)
// {
//     ip = theIP;
//     port = new Port(thePortQueueSize);
//     nearestRouter = UNKOWN;

// }


// QSharedPointer<Packet> Host::createPacket(IP destination , QString data)
// {
//     Packet pack(ip ,destination , data , Data , version);
//     return QSharedPointer<Packet>::create(pack);
// }




// void Host::getIpFromDHCPServer()
// {
//     Packet pack(ip , nearestRouter , "IP_REQUEST" , DHCP , version);
//     port->sendPacket(QSharedPointer<Packet>::create(pack));
// }



// void Host::onClock(NetworkState ns)
// {
//     currentState = ns;
//     if(currentState == DHCPDATA)
//         getIpFromDHCPServer();
//     else
//         handleIncomingPackets();
// }

// void Host::sendPacketTo(QString desttination)
// {

//     Packet pack(ip , desttination , " - " , Data , version);
//     port->sendPacket(QSharedPointer<Packet>::create(pack));

// }

// // TODO :

// // void Host::handleIncomingPackets()
// // {
// //     while(!port->isQueueEmpty())
// //     {
// //         QSharedPointer<Packet> p = port->dequeue();

// //         if(p->getData() == "DHCP_ANSWER" && p->getType() == DHCPDATA)
// //         {
// //             ip = p->getDestiantionAddr();
// //             nearestRouter = p->getSourceAddr();
// //         }

// //         else if(p->getType() == SENDDATA)
// //         {
// //             QSharedPointer<Packet> recieved = p;
// //             if(p->maskedPacket)
// //                 recieved = p->getInnerPacket();
// //             qDebug() << "Host " + recieved->getDestiantionAddr() + " Recieved Packet from " + recieved->getSourceAddr()
// //                             + " data : " + recieved->getData();
// //             recieved->printLogs();
// //         }
// //     }
// // }

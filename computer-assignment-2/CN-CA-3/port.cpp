#include "port.h"

Port::Port(int maxq , QObject *parent): QObject{parent}{
    maxQueueSize = maxq;
}
void Port::increasePacketsLifeSpan(){
    for(auto it = queue.cbegin() ; it!=queue.cend() ; it++)
        (*it)->increaseLifeSpan();
}
void Port::recievePacket(QSharedPointer<Packet> pack){
    if(maxQueueSize == queue.size()){
        std::cout << "overflow occured" << std::endl ;


    }else{
        queue.enqueue(pack);
    }
}
void Port::sendPacket(QSharedPointer<Packet> pack){
    emit newPacketArrived(pack);
}

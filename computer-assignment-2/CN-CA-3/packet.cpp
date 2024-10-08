#include "packet.h"

Packet::Packet(IP source ,IP dest ,IP _data , TypeOfPacket _type , VersionOfIP _v)
{
    generateTime = QTime::currentTime().toString("hh:mm:ss");
    data = _data;
    lifeSpan = 0;
    ipVer = _v;
    sourceAddr = source;
    destinationAddr = dest;
    type = _type;
}

void Packet::increaseLifeSpan(int val)
{
    lifeSpan+=val;
}

QString Packet::getPacket(){
    return data + " TO " + destinationAddr + " FROM " + sourceAddr + " @ " + generateTime;
}

void Packet::printLogs()
{
    for(int i = 0 ; i < logs.size(); i++)
        qDebug() << logs[i] << "\n" ;
}

void  Packet::addLog(QString log)
{
    logs.append(log);

}

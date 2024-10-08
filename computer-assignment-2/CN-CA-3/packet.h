#ifndef PACKET_H
#define PACKET_H


#include <QObject>
#include <QTime>
#include "utility.hpp"

class Packet{
public:
    explicit Packet(IP source ,IP dest ,QString _data ,TypeOfPacket _type , VersionOfIP _v);


    void increaseLifeSpan(int val = 1);

    QString getPacket();

    IP getDestiantionAddr() {return destinationAddr;}

    IP getSourceAddr() {return sourceAddr;}

    IP getData() {return data;}


    TypeOfPacket getType() {return type;}

    void setDestination(IP dest) {destinationAddr = dest;}

    void setSource(IP source) {sourceAddr = source;}

    void setData(QString d){ data = d;}

    void setTime(QString time){generateTime = time;}

    void addLog(QString log);

    void printLogs();

    VersionOfIP getIPVersion(){return ipVer;}


private:
    IP sourceAddr;
    IP destinationAddr;
    QString data;
    TypeOfPacket type;
    QString generateTime;
    QVector<QString> logs;
    int lifeSpan;
    VersionOfIP ipVer;
};




#endif // PACKET_H

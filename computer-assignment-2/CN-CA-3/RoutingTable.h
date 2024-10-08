#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H


#include "port.h"
#include "utility.hpp"
#include <QObject>
#include <QQueue>
#include <iostream>



typedef struct route{
    IP destination;
    int cost;
    IP nextHop;
    route();
    route(const IP ip,const int _cost , const IP nh);
} route;

class RTable: public QObject {
    Q_OBJECT
public:
    QMap<IP ,  route> getRoutingTable();
    void inseartRecord (IP theIP , route _route);
private:
    QMap<IP ,  route> routingTable;

};





#endif // ROUTINGTABLE_H

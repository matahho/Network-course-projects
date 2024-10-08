#ifndef FORWARDTABLE_H
#define FORWARDTABLE_H

#include <QObject>
#include <QVector>
#include "port.h"       // Assuming these headers define IP, Port, and NodeType
#include "utility.hpp"  // Include necessary headers

typedef struct {
    IP nextHopIP;
    IP subnetMask;
    IP subnetID;
    Port* port;
    TypeOfNode nextHopType;
} forward;

class ForwardTable : public QObject {
    Q_OBJECT
public:
    QVector<forward*> getForwardTable();
    void insertIntoTable(IP nextHopIP, IP subnetMask, IP subnetID, Port* port, TypeOfNode nextHopType);
private:
    QVector<forward*> forwardingTable;
};

#endif // FORWARDTABLE_H

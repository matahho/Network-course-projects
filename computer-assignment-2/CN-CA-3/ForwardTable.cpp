#include "ForwardTable.h"

void ForwardTable::insertIntoTable(IP nextHopIP, IP subnetMask, IP subnetID, Port* port, TypeOfNode nextHopType) {
    forward* entry = new forward{nextHopIP, subnetMask, subnetID, port, nextHopType};
    forwardingTable.append(entry);
}

QVector<forward *> ForwardTable::getForwardTable() {
    return forwardingTable;
}

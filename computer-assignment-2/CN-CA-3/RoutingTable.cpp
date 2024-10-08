#include "RoutingTable.h"


// Default constructor for route
route::route() : destination(), cost(0), nextHop() {}

// Parameterized constructor for route
route::route(const IP ip, const int _cost, const IP nh)
    : destination(ip), cost(_cost), nextHop(nh) {}

void RTable::inseartRecord(IP theIP, route _route) {
    routingTable[theIP] = _route;
}
QMap<IP, route> RTable::getRoutingTable() {
    return routingTable;
}

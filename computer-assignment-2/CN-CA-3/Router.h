#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include "Node.h"
#include "RoutingTable.h"
#include "ForwardTable.h"

class Router : public Node {
public:
    explicit Router(IP _ip, VersionOfIP v, int _portQueueSize, bool AmIInTheBorder = false);
    bool isInTheBorder = false;
private:
    RTable routingTable;
    ForwardTable forwardingTable;

};

#endif // ROUTER_H

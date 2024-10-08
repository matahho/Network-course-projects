#include "Router.h"

Router::Router(IP _ip, VersionOfIP v, int _portQueueSize, bool AmIInTheBorder)
    : Node(_ip, v, _portQueueSize),
    routingTable(),
    forwardingTable() {
    isInTheBorder = AmIInTheBorder;
}


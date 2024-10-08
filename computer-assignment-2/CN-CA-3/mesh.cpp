#include "mesh.h"

Mesh::Mesh(IP _baseIP, QObject *parent)
    : QObject{parent}, baseIP{_baseIP} {}

Mesh::~Mesh()
{
    for (int i = 0; i < routers.size(); ++i)
        for (int j = 0; j < routers[i].size(); ++j)
            delete routers[i][j];

    for (int i = 0; i < hosts.size(); ++i)
        delete hosts[i];

    for (int i = 0; i < threads.size(); ++i)
        delete threads[i];
}

void Mesh::createCluster()
{
    createThreads(n * (n + 2));
    createRoutersAndHosts();
    connectAllRouters();
    connectHostsToRouters();
    moveNodesToThread();
}

void Mesh::createThreads(int n)
{
    for (int i = 0; i < n; ++i)
        threads.append(new QThread);
}

void Mesh::createRoutersAndHosts()
{
    for (int i = 0; i < n; ++i) {
        QVector<Router*> temp;
        for (int j = 0; j < n; ++j) {
            temp.append(new Router(baseIP + "." + QString::number(j + i * n + 1) + ".1", IPV6, 100));
        }
        routers.append(temp);
    }

    for (int i = 0; i < 2 * n; ++i)
        hosts.append(new Host("NOTHING", IPV6, 10));
}

void Mesh::connectPorts(Port* p1, Port* p2)
{
    QObject::connect(p1, &Port::newPacketArrived, p2, &Port::recievePacket);
    QObject::connect(p2, &Port::newPacketArrived, p1, &Port::recievePacket);
}

void Mesh::connectRouters(Router* r1, Router* r2)
{
    // TO DO
}

void Mesh::connectRouterToHost(Router* r, Host* h)
{
    // TO DO
}

void Mesh::connectAllRouters()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j - 1 >= 0)
                connectRouters(routers[i][j], routers[i][j - 1]);
            if (i - 1 >= 0)
                connectRouters(routers[i][j], routers[i - 1][j]);
            if (j + 1 < n)
                connectRouters(routers[i][j], routers[i][j + 1]);
            if (i + 1 < n)
                connectRouters(routers[i][j], routers[i + 1][j]);
        }
    }
}

void Mesh::connectHostsToRouters()
{
    for (int j = 0; j < n; ++j) {
        connectRouterToHost(routers[0][j], hosts[2 * j]);
        connectRouterToHost(routers[0][j], hosts[2 * j + 1]);
    }
}

void Mesh::moveNodesToThread()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            routers[i][j]->moveToThread(threads[i * n + j]);

    for (int i = 0; i < 2 * n; ++i)
        hosts[i]->moveToThread(threads[n * n + i]);

    for (int i = 0; i < threads.size(); ++i)
        threads[i]->start();
}

QVector<Router*> Mesh::getEdgeRouters()
{
    QVector<Router*> edgeRouters;
    for (int i = 0; i < routers.size(); ++i) {
        edgeRouters.append(routers[n - 1][i]);
        routers[n - 1][i]->isInTheBorder = true;
    }
    for (int i = 0; i < routers.size(); ++i) {
        routers[i][n - 1]->isInTheBorder = true;
        edgeRouters.append(routers[i][n - 1]);
    }
    return edgeRouters;
}

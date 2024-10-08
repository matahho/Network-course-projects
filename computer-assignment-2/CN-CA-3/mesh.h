#ifndef MESH_HPP
#define MESH_HPP

#include <QObject>
#include <QVector>
#include <QThread>
#include "utility.hpp"
#include "Router.h"
#include "Host.h"

class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(IP _baseIP, QObject *parent = nullptr);
    ~Mesh();
    QVector<Router*> getEdgeRouters();
    void createCluster();
    QVector<QVector<Router*>> getRouters() { return routers; }

private:
    void createRoutersAndHosts();
    void connectAllRouters();
    void connectHostsToRouters();
    void moveNodesToThread();
    void createThreads(int n);
    void connectPorts(Port* p1, Port* p2);
    void connectRouters(Router* r1, Router* r2);
    void connectRouterToHost(Router* r, Host* h);

    IP baseIP;
    QVector<QThread*> threads;
    QVector<QVector<Router*>> routers;
    QVector<Host*> hosts;
    int n = 4;
};

#endif // MESH_HPP

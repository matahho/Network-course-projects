#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QThread>
#include <QDebug>

class Router : public QObject
{
    Q_OBJECT

public:
    explicit Router(QObject *parent = nullptr);
    int getId();

public slots:
    void start();

private:
    inline static uint routerID = 0;
    const uint _id;
};

#endif // ROUTER_H

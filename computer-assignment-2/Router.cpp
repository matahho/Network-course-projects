#include "Router.h"

Router::Router(QObject *parent)
    : QObject(parent),
    _id(++Router::routerID)
{

}

int Router::getId()
{
    return _id;
}

void Router::start()
{
    qDebug() << "Router" << this->getId() << "is running on thread:" << QThread::currentThread();
}

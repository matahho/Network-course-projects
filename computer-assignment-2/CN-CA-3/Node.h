#ifndef NODE_H
#define NODE_H

#include "utility.hpp"
#include <QObject>
#include <QDebug>
#include <QSharedPointer>


class Node : public QObject
{
    Q_OBJECT


public:
    explicit Node(IP theIP
                  ,VersionOfIP theVersion
                  ,int thePortQueueSize
                  ,QObject *parent = nullptr
                );

    VersionOfIP version;

    QVector<int> splitIpIntoInt ( QString ip);


    int getPortQueueSize();

protected:
    NetworkState currentState;
    IP ip;
    int portQueueSize;

public slots:
    virtual void onClock(NetworkState ns){currentState = ns;};
};


#endif // NODE_H

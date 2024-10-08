#include "node.h"



Node::Node(IP theIP ,VersionOfIP theVersion  , int thePortQueueSize, QObject *parent): QObject{parent}
{
    ip = theIP;
    version = theVersion;
    portQueueSize = thePortQueueSize;
}


QVector<int> Node::splitIpIntoInt(QString ip)
{
    QStringList parts = ip.split('.');
    QVector<int> result;


    for (const QString& part : parts){
        bool isTansformPossible;

        int num = part.toInt(&isTansformPossible);

        if (isTansformPossible){
            result.append(num);
        }
    }
    return result;
}


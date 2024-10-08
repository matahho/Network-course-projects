#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <QString>
#include<QVector>

// Network utility
enum NetworkState {SENDDATA, RouterGreeting ,DHCPDATA ,NeighborIdentification};


// Node utility
enum TypeOfNode {HOST , LOCAL_ROUTER ,EXTERNAL_ROUTER};

// Cluster utility
enum TypeOfCluster { RingStar, Mesh};


// IP utility
typedef QString IP;

enum VersionOfIP {IPV4, IPV6};


// functions utility
QString getBaseIP(const IP& theIP);


//packet
enum TypeOfPacket { Data, DistanceVec , DHCP };


// other
QString UNKOWN = "NOBODY";




#endif // UTILITY_HPP

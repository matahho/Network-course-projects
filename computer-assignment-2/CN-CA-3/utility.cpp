#include "utility.hpp"


QString getBaseIP(const IP& theIP){
    QStringList eachPart = theIP.split('.');
    if (eachPart.size() >= 2) {
        return eachPart[0] + "." + eachPart[1];
    }
    else {
        return "Not correct IP address !";
    }

}

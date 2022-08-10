

#include <NetAddress.h>

//=============================================================================
// NetAddress interface
//=============================================================================

NetAddress  :: NetAddress   (){;}  // sets up object

void NetAddress::set(IPAddress _ip, int _port) {
    destinationIP = _ip;
    destinationPort = _port;
}

IPAddress NetAddress :: getIP (){
    return destinationIP;
}

int NetAddress :: getPort(){
    return destinationPort;
}


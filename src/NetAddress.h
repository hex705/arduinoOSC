
#ifndef NetAddress_h
#define NetAddress_h


#include <Ethernet.h>


//=============================================================================

class NetAddress {
    
 protected:
	
    IPAddress destinationIP;
    int       destinationPort; 
    
public:

    
    NetAddress(void);
    void set (IPAddress, int);
    IPAddress getIP();
    int getPort();

    
};


#endif


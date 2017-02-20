#ifndef OscUDP_h 
#define OscUDP_h

#include "OSCMessage.h"


// added this for out address in UDP
#include <Ethernet.h>
#include <EthernetUdp.h>

// adding this to move netaddress interface out for all UDP
#include <NetAddress.h>

/*
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

*/

//=============================================================================
class OscUDP {

protected:
	
	OSCMessage msgIN;
	
	EthernetUDP *udp; 
	
	NetAddress *destination;
	// add the outgoing IP and PORT
    IPAddress outIP;
    int       outPort;
  
    
public:

	OscUDP();
	
	void begin (EthernetUDP &);
	
    void send(OSCMessage &, NetAddress  &);
    void send(OSCMessage &, IPAddress, int);

	void listen();
    
};





#endif
#ifndef OscUDPwifi_h 
#define OscUDPwifi_h

#include "OSCMessage.h"


// added this for out address in UDP
#include <WiFiUdp.h>

// adding this to move netaddress interface out for all UDP
#include <NetAddress.h>




//=============================================================================
class OscUDPwifi {

protected:
	
	OSCMessage msgIN;
	
	WiFiUDP *udpWifi; 
	
	NetAddress *destination;
	// add the outgoing IP and PORT
    IPAddress outIP;
    int       outPort;
  
    
public:

	OscUDPwifi();
	
	void begin (WiFiUDP &);
	
    void send(OSCMessage &, NetAddress  &);
    void send(OSCMessage &, IPAddress, int);

	void listen();
    
};


#endif
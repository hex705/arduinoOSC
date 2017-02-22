#ifndef OscUDPwifi_h 
#define OscUDPwifi_h

#include "OscMessage.h"


// added this for out address in UDP
#include <WiFiUdp.h>

// adding this to move netaddress interface out for all UDP
#include <NetAddress.h>




//=============================================================================
class OscUDPwifi {

protected:
	
	OscMessage msgIN;
	
	WiFiUDP *udpWifi; 
	
	NetAddress *destination;
	// add the outgoing IP and PORT
    IPAddress outIP;
    int       outPort;
  
    
public:

	OscUDPwifi();
	
	void begin (WiFiUDP &);
	
    void send(OscMessage &, NetAddress  &);
    void send(OscMessage &, IPAddress, int);

	void listen();
    
};


#endif
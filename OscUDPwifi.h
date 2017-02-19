#ifndef OscUDPwifi_h 
#define OscUDPwifi_h

#include "OSCMessage.h"


// added this for out address in UDP
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



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
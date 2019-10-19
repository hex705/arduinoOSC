#ifndef OscUDPwifiEsp_h
#define OscUDPwifiEsp_h

#include "OscMessage.h"


// added this for out address in UDP
// #include <WiFiUdp.h>

#include <WiFiEspUdp.h> // for shield

// adding this to move netaddress interface out for all UDP
#include <NetAddress.h>


//=============================================================================
class OscUDPwifiEsp {

protected:

	OscMessage msgIN;

	//WiFiUDP *udpWifi;
	WiFiEspUDP *udpWifiEsp; // for shield

	NetAddress *destination;
	// add the outgoing IP and PORT
    IPAddress outIP;
    int       outPort;


public:

	OscUDPwifiEsp();

	//void begin (WiFiUDP &);
	void begin (WiFiEspUDP &);// for shield

    void send(OscMessage &, NetAddress  &);
    void send(OscMessage &, IPAddress, int);

	void listen();

};


#endif

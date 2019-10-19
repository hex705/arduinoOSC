#ifndef OscUDP_h
#define OscUDP_h
#include "OscMessage.h"

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include <Udp.h>
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// adding this to move netaddress interface out for all UDP
#include <NetAddress.h>

//=============================================================================
class OscUDP {

protected:

	OscMessage msgIN;

  UDP *udp;
  // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

	NetAddress *destination;

  // add the outgoing IP and PORT
  IPAddress outIP;
  int       outPort;


public:

	OscUDP();
  void begin (UDP &u) { udp = &u; }

	// common functions
	void send(OscMessage &);
  void send(OscMessage &, NetAddress  &);
  void send(OscMessage &, IPAddress, int);

	void listen();

};





#endif

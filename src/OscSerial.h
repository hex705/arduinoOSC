#ifndef OscSerial_h
#define OscSerial_h

#include "OscMessage.h"

#include <SLIPEncodedSerial.h>

//=============================================================================
class OscSerial  {
	
private:
	OscMessage msgIN;
	SLIPEncodedSerial *slip;

public:
	// constructor
	OscSerial( );
	void begin( Stream & );
	void send( OscMessage & );
	void listen( );

};

#endif

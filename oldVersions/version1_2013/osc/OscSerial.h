#ifndef OscSerial_h 
#define OscSerial_h

#include "OSCMessage.h"

#include "SLIPEncodedSerial.h"
#include <HardwareSerial.h>

//=============================================================================
class OscSerial  {	
	

private:
	OscMessage msgIN;
	SLIPEncodedSerial *slip;

public:	
	// constructor
	OscSerial( );
	
	void begin( HardwareSerial & );
	void send( OscMessage & ); 	
	void listen( );
	
};





#endif
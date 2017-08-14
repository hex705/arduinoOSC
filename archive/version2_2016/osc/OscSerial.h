#ifndef OscSerial_h 
#define OscSerial_h

#include "OscMessage.h"

#if defined(CORE_TEENSY)|| defined(__AVR_ATmega32U4__)
#include <SLIPEncodedUSBSerial.h>
//SLIPEncodedUSBSerial SLIPSerial(Serial);
#else
// any hardware serial port
#include <SLIPEncodedSerial.h>
//SLIPEncodedSerial SLIPSerial(Serial);
#endif

//#include "SLIPEncodedSerial.h"
#include <HardwareSerial.h>

//=============================================================================
class OscSerial  {	
	

private:
	OscMessage msgIN;

	#if defined(CORE_TEENSY)|| defined(__AVR_ATmega32U4__)
	  SLIPEncodedUSBSerial *slip;
        #else
	  SLIPEncodedSerial *slip;
	#endif

public:	
	// constructor
	OscSerial( );
	
        #if defined(CORE_TEENSY)|| defined(__AVR_ATmega32U4__)
          // add to see if flora can work
            void beginUSB( Serial_ & );
	  // end add
        #else
	    void begin( HardwareSerial & );
        #endif
      
	void send( OscMessage & ); 	
	void listen( );
	
};





#endif
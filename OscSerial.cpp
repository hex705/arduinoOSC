#include <OscSerial.h>




void oscEvent(OscMessage &);

//=============================================================================
// OSC_Serial Wrapper
//=============================================================================

/*
// old wrapper constructor
OscSerial::OscSerial(HardwareSerial &s) {
	slip = new SLIPEncodedSerial(s);	 
}
*/

OscSerial::OscSerial() {
	;
}

// based on example from CNMAT
// http://cnmat.berkeley.edu/book/export/html/11389

#if defined(CORE_TEENSY)|| defined(__AVR_ATmega32U4__)

  void OscSerial::beginUSB(Serial_ &s) {
	slip = new SLIPEncodedUSBSerial(s);	 
  }

#else

  void OscSerial::begin(HardwareSerial &s) {
	slip = new SLIPEncodedSerial(s);	 
  }

#endif


// end add remove if this fails

// Non-blocking version
void OscSerial::listen() {
	int size;
	if( (size = slip->available()) > 0) {
		while(size--) msgIN.fill(slip->read());
	}  
	if (!slip->endofPacket()) return;
	
	if (!msgIN.hasError()) {
		oscEvent(msgIN);
	}	
	
	// change this line to make this work.
	//msgIN.reset();  // this is the old interface... 
	//msgIN.~OscMessage();  // this was wrong -- but it looked good from afar.
     msgIN.empty();
}

/*
// Blocking Version -- do not use, left there for reference
void OscSerial::listen() {	
	int size;
	while(!slip->endofPacket()) {
		if( (size = slip->available()) > 0) {
		   while(size--) msgIN.fill(slip->read());
		}  
	}
		
	if(!msgIN.hasError()) {
		oscEvent(msgIN);
	}

	// get the OSC message ready for the next one
        msgIN.reset();
}
*/

void OscSerial::send(OscMessage &msg) {
	msg.send(*slip);
	slip->endPacket();
	msg.empty();
}



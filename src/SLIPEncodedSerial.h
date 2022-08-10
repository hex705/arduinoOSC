/*
Extends the Serial class to encode SLIP over serial
*/

#ifndef SLIPEncodedSerial_h
#define SLIPEncodedSerial_h
#include <Arduino.h>
#include <Stream.h>
#include <HardwareSerial.h>


class SLIPEncodedSerial: public Stream{

private:
	enum erstate {CHAR, FIRSTEOT, SECONDEOT, SLIPESC } rstate;

	//the serial port used
	Stream * serial;


public:

	//the serial port used
	SLIPEncodedSerial(Stream & );


	int available();
	int read();
	int peek();
	void flush();
	
	//SLIP specific method which ends a transmittedpacket
	void endPacket();
	// SLIP specific method which indicates that an EOT was received
	bool endofPacket();


//the arduino and wiring libraries have different return types for the write function
#ifdef WIRING
	void write(uint8_t b);
#else
	//overrides the Stream's write function to encode SLIP
	size_t write(uint8_t b);
	//using Print::write;
#endif

};


#endif
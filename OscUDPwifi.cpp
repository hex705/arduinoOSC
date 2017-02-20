#include <OscUDPwifi.h>


void oscEvent(OSCMessage &);


//=============================================================================
// OSC_UDP Wrapper
//=============================================================================

// TODO: write similar wrapper class using the UDP interface 
// waiting to solve the blocking kink on the Serial one first

OscUDPwifi::OscUDPwifi( ){
    
	;
    
}

void OscUDPwifi::begin(WiFiUDP &u){
    
    udpWifi = &u;  // &u ? u
    
}


void OscUDPwifi::send(OSCMessage &msg, NetAddress &na){
    OscUDPwifi::send (msg, na.getIP(), na.getPort() );
}


void OscUDPwifi::send(OSCMessage &msg, IPAddress outIp, int outPort) {

    // SEND BASED ON THIS :
    // http://cnmat.berkeley.edu/library/oscuino/omessage
    
    // we need to do some magic here
    udpWifi->beginPacket(outIp, outPort);
    msg.send(*udpWifi); // send the bytes to the SLIP stream
    udpWifi->endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message
    
}

void OscUDPwifi::listen() {
    
    // need a non-blocking method to read bytes from the UDP stream
    // parsePacket us analogous to available
    int UDPpacketSize;
  
	if( (UDPpacketSize = udpWifi->parsePacket())  > 0) {
		while(UDPpacketSize--) msgIN.fill(udpWifi->read());
	} else {
        return; // i am not sure that works but lets see
                //  i think it says if packet is <= 0 return
    }

 
	
	if (!msgIN.hasError()) {
		oscEvent(msgIN);
	}
	
	//msgIN.reset();
    //msgIN.~OSCMessage(); // <-- see serial for note
    msgIN.empty(); // using ~OSCMessage seems to block serial.. more testing needed.

}


/*
//=============================================================================
// NetAddress interface
//=============================================================================


NetAddress  :: NetAddress   (){;}  // sets up object

void NetAddress::set(IPAddress _ip, int _port) {
    destinationIP = _ip;
    destinationPort = _port;
}

IPAddress NetAddress :: getIP (){
    return destinationIP;
}

int NetAddress :: getPort(){
    return destinationPort;
}
*/

#include <OscUDP.h>


void oscEvent(OscMessage &);


//=============================================================================
// OSC_UDP Wrapper
//=============================================================================

// TODO: write similar wrapper class using the UDP interface 
// waiting to solve the blocking kink on the Serial one first

OscUDP::OscUDP( ){
    
	;
    
}

void OscUDP::begin(EthernetUDP &u){
    
    udp = &u;  // &u ? u
    
}


void OscUDP::send(OscMessage &msg, NetAddress &na){
    OscUDP::send (msg, na.getIP(), na.getPort() );
}


void OscUDP::send(OscMessage &msg, IPAddress outIp, int outPort) {

    // SEND BASED ON THIS :
    // http://cnmat.berkeley.edu/library/oscuino/omessage
    
    // we need to do some magic here
    udp->beginPacket(outIp, outPort);
    msg.send(*udp); // send the bytes to the SLIP stream
    udp->endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message
    
}

void OscUDP::listen() {
    
    // need a non-blocking method to read bytes from the UDP stream
    // parsePacket us analogous to available
    int UDPpacketSize;
  
	if( (UDPpacketSize = udp->parsePacket())  > 0) {
		while(UDPpacketSize--) msgIN.fill(udp->read());
	} else {
        return; // i am not sure that works but lets see
                //  i think it says if packet is <= 0 return
    }

 
	
	if (!msgIN.hasError()) {
		oscEvent(msgIN);
	}
	
	msgIN.reset();
    

}



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


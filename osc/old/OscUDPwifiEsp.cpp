#include <OscUDPwifiEsp.h>


void oscEvent(OscMessage &);


//=============================================================================
// OSC_UDP Wrapper
//=============================================================================

// TODO: write similar wrapper class using the UDP interface 
// waiting to solve the blocking kink on the Serial one first

OscUDPwifiEsp::OscUDPwifiEsp( ){
    
	;
    
}

// void OscUDPwifi::begin(WiFiUDP &u){
    
//     udpWifi = &u;  // &u ? u
    
// }

// *** for shield
void OscUDPwifiEsp::begin(WiFiEspUDP &u){
    
    udpWifiEsp = &u;  // &u ? u
   
}
// end for shield ***


void OscUDPwifiEsp::send(OscMessage &msg, NetAddress &na){
    OscUDPwifiEsp::send (msg, na.getIP(), na.getPort() );
}


void OscUDPwifiEsp::send(OscMessage &msg, IPAddress outIp, int outPort) {

    // SEND BASED ON THIS :
    // http://cnmat.berkeley.edu/library/oscuino/omessage
    
    // we need to do some magic here
    udpWifiEsp->beginPacket(outIp, outPort);
    msg.send(*udpWifiEsp); // send the bytes to the SLIP stream
    udpWifiEsp->endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message
    
}

void OscUDPwifiEsp::listen() {
    
    // need a non-blocking method to read bytes from the UDP stream
    // parsePacket us analogous to available
    int UDPpacketSize;
  
	if( (UDPpacketSize = udpWifiEsp->parsePacket())  > 0) {
		while(UDPpacketSize--) msgIN.fill(udpWifiEsp->read());
	} else {
        return; // i am not sure that works but lets see
                //  i think it says if packet is <= 0 return
    }

 
	
	if (!msgIN.hasError()) {
		//oscEvent(msgIN);
	}
	
	//msgIN.reset();
    //msgIN.~OscMessage(); // <-- see serial for note
    msgIN.empty(); // using ~OscMessage seems to block serial.. more testing needed.

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

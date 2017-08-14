
// MESSAGE PROTOCOL OBJECT
#include <OscUDP.h>


// hardware libraries to access use the shield
#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>


// arduino needs us to start ethernet, then start UDP
// http://arduino.cc/en/Reference/EthernetBegin


// Enter a MAC address and IP address for your SHIELD.
// The IP address will be dependent on your local network
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// listeningIP ==  SHIELD initialization IP
IPAddress listeningIP(141,117,45,176); // you need to set this

// listening -- port
unsigned int listeningPort = 12001;      // local port to listen on


// speaking 
// set up our destination NODE
NetAddress destination;
IPAddress destinationIP( 141,117,45,82 ); 
int destinationPort = 12000;




// setup a UDP object
EthernetUDP UDP;

// OUR OSC MESSAGE OBJECT
OscUDP etherOSC;  

// timer variable
long timer;



void setup() {
  
  // some local debug -- we can see this in serial port
  Serial.begin(9600);
  
  // start ethernet on the shield
  Ethernet.begin(mac,listeningIP);
  
  // print Arduino's IP
  Serial.println(Ethernet.localIP());
  
  // start UDP object, listening on port listeningPort
  UDP.begin(listeningPort);
  
  // set up our communication protocol
  // pass the UDP object to OSC
  etherOSC.begin(UDP);
  
  // define our destination location
  destination.set(destinationIP, destinationPort);
  
  // local hardware setup 
  pinMode(2, OUTPUT); // note can't use 13 for UDP becasue of shield
  Serial.println("starting");
  
}

void loop() {
  // send a message every 100 ms
  
  // avoid using delay() since it just blocks everything  
  // so here is a simple timer that controls how often we send
  long now = millis();
  if (now-timer > 100) {
    // build a message, start with address pattern
    OscMessage msg("/arduinoEthernetSays");
    
    // add a data point (can add many)
    msg.add(digitalRead(2)); // <-- this could be any data -- its our LED state 
    
    // actually do the sending
    etherOSC.send(msg, destination);
    
    // reset the timer
    timer = now;
    
    // local debug -- you can get rid of this
    Serial.println("send one");
  } // end if
  
  
  // important! non-blocking listen routine
  etherOSC.listen();  // if there is data waiting, this will trigger OSC EVENT

}


void oscEvent(OscMessage &m) { // *note the & before msg
  // receive a message 
  Serial.println("got a message");
  // in arduino, we plug events in the EVENT method
  m.plug("/led", myFunction); 
  
}


void myFunction(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  Serial.println("led");
  
  // getType takes position as a parameter
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(2, LOW);
  if (value == 1) digitalWrite(2, HIGH);
  
}

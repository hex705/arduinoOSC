
#include <OscSerial.h>

// tile support libraries
//#include <EthernetUdp.h>
//#include <SPI.h>  

OscSerial oscSerial;
long timer;

void setup() {
  Serial.begin(9600);
  oscSerial.begin(Serial); 
  pinMode(13, OUTPUT);
}

void loop() {
  //  limits sends to every 100 mS
    if (millis()>= serialTimerEnd) {
        sendOscSerial();
        serialTimerEnd = millis() + serialTimerInterval;
    }

    // important! this is needed in order to receive messages  
    oscSerial.listen();
}
// incoming messages will arrive here
void oscEvent(OscMessage & msg) {
    // handle data here 
    // OR
    // route messages using the "plug" functionality

    // this example redirects messages called "/incoming" to myFunction (below) 
    msg.plug("/incoming", myFunction);
}

// plugged function
void myFunction(OscMessage & msg) {
    // get the data out of the message 
    int data = msg.getInt(0);
    digitalWrite(13,data);
}
// send OSC Serial messages
void sendOscSerial() {
    OscMessage msg("/outgoing"); // this could be any pattern
    msg.add(analogRead(A0)); // this could be any data
    oscSerial.send(msg);
}

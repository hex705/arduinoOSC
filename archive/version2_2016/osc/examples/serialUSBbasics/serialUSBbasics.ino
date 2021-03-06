#include <OscSerial.h>

// tile support
//#include <EthernetUdp.h>
//#include <SPI.h>

OscSerial oscSerial;
int baudRate = 9600;

long serialTimerEnd;
long serialTimerInterval = 100;

void setup() {
    Serial.begin(baudRate); // has to be serial1 not Serial
    oscSerial.beginUSB(Serial); // has to be beginUSB not just begin
    pinMode(13,OUTPUT);
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
    OscMessage msg("/pigsRUnFast"); // this could be any pattern
    msg.add(analogRead(A0)); // this could be any data
    oscSerial.send(msg);
}

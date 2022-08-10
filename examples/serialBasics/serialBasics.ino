#include <OscSerial.h>

int baudRate = 9600;
OscSerial oscSerial;
long serialTimerEnd;
long serialTimerInterval = 100;

void setup() {
    Serial.begin(baudRate);
    while (!Serial);
    oscSerial.begin(Serial);
    pinMode(13,OUTPUT); // use builtin led to visualize data from processing

    // on the Flora or Leonardo, use Serial1 to communicate with USB and Serial to
    // communicate with a radio
}

void loop() {
    //  Serial1.println("hi mom");
    
    //  timer -- limits sends to every 100 mS 
    if (millis()>= serialTimerEnd) {
        sendOscSerial();
        serialTimerEnd = millis() + serialTimerInterval; // see line 6 for timer interval
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
    digitalWrite(13, data);
}

// send OSC Serial messages
void sendOscSerial() {
    OscMessage msg("/outgoingSerial"); // this could be any pattern
    msg.add(113); // this could be any data
    oscSerial.send(msg);
}

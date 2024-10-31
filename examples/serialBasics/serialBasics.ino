#include <OscSerial.h>

int baudRate = 9600;
OscSerial oscSerial;
long serialTimerEnd;
long serialTimerInterval = 100;
int ledPin = 13;

float piFloat = 3.21;

void setup() {
    Serial.begin(baudRate);
    oscSerial.begin(Serial);
    pinMode(ledPin,OUTPUT); // use builtin led to visualize data from processing

    // on the Flora or Leonardo, use Serial1 to communicate with USB and Serial to
    // communicate with a radio
}

void loop() {

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
    digitalWrite(ledPin, data);
}

// send OSC Serial messages
void sendOscSerial() {
    OscMessage msg("/outgoingSerial"); // this could be any pattern
      msg.add(1.23f); // the 'f' to designate float is need on esp32 (oct 2024)
      //msg.add(piFloat); // the 'f' to designate float is need on esp32 (oct 2024)
      msg.add(456); // this could be any data
      msg.add(789); // this could be any data
    oscSerial.send(msg);
}

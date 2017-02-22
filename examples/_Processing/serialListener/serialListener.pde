import processing.serial.*;
import oscP5.*;

int serialTimerEnd;
int serialTimerInterval = 250;
Serial proSerial;

String serialName = "/dev/cu.usbmodemXXXX"; // put the name of your serial port
int baudRate = 9600; // set your baud rate
OscSerial oscSerial;

void setup() {
    // You'll find your serial device in this list 
    println(Serial.list());
    //start serial 
    proSerial = new Serial(this, serialName, baudRate);
    oscSerial = new OscSerial(this, proSerial);
}

void draw() {
    if (millis()>= serialTimerEnd) {
        sendOscSerial();
        serialTimerEnd = millis() + serialTimerInterval;
    }
}

// Listen for ALL OSC messages
void oscEvent(OscMessage incoming) {
    // all the received messages come here
    println(incoming);
    int val0 = incoming.get(0).intValue();
    println(val0);
}

// send OSC serial messages 
void sendOscSerial() {
    OscMessage msg = new OscMessage("/incoming");
    // v = 0 if mouse on left side of sketch, 1 if on right
    // move mouse to turn built in LED :: ON /OFF
    int v = 0;
    if ( mouseX>width/2) v=1;
    msg.add( v ); 
    oscSerial.send(msg);
}
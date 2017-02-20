import netP5.*;
import oscP5.*;

OscP5 oscNet;
int listeningPort = 12000;
int netTimerEnd;
int netTimerInterval = 250;

// Someone to talk to
NetAddress destination;
String destinationIP = "127.0.0.1";
int destinationPort = 1200;

// font stuff
PFont f;

//global stuff to draw with
String addPattern ="";
int theNumber;

void setup() {
  size(1000,150);
    oscNet = new OscP5(this, listeningPort);

    destination = new NetAddress(destinationIP, destinationPort);
    
  // font stuff
  f = createFont("SourceCodePro-Regular.vlw", 50);
  textFont(f);
  textAlign(CENTER, CENTER);
  
}

void draw() {
    if (millis()>= netTimerEnd) {
        sendOscNet(); // send to network destination
        netTimerEnd = millis() + netTimerInterval;
    }
}

// Listen for ALL OSC messages
void oscEvent(OscMessage incoming) {
    // all the received messages come here
    println(incoming);
    addPattern = incoming.addrPattern();
     text("incoming" , 100, height/4);
      text( addPatt, 150 , height/4+30);
     
    theNumber = incoming.get(0).intValue();
}
// send network messages to destination
void sendOscNet() {
    OscMessage msg = new OscMessage("/outgoingInternet");
    msg.add(mouseX); // this could be any data 
    oscNet.send(msg, destination);
}
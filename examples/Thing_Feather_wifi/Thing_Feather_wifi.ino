/// this is a first successful test of OSC over udpwifi -- using esp8266 and our wrapper.

// significant changes to our library needed -- also need to change templates.
// need to update:: 
// data   .h and .cpp
// timing .h and .cpp
// message  .h and .cpp
//NOTE CNMAT MESSAGE class got renamed OSCMessage  from OscMessage
// this change breaks our UDP and Serial wrappers for arduino but it is a quick fix.
// all template oscEvents and oscSends need the class renamed.
//  also
// OscMessage.reset() no longer exists
// replace with ~OSCMessage() in .cpp wrapper files above.


#include <OscUDPwifi.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCData.h>

WiFiUDP wifiUDP;

char packetBuffer[255];
unsigned int localPort = 9999;
OscUDP oscUDP; 
NetAddress destination;


// The IP address of a computer you are trying to reach
IPAddress destinationIP(141, 117, 245, 84);
int destinationPort = 12000;

void setup() {
Serial.begin(9600);

WiFi.begin("NETART", "rapiddiamond499");

// wait for wifi to connect
Serial.print("[Connecting]: ");
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
Serial.println(WiFi.localIP());
// startUDP
wifiUDP.begin(localPort);

oscUDP.begin(wifiUDP);  // got that 

destination.set(destinationIP, destinationPort);

}

void loop()
{
   sendOscNet();
   delay(500);
}
// send OSC Internet messages
void sendOscNet() {
   OSCMessage msg("/thingRSays"); // this could be any pattern
    msg.add(analogRead(A0)); // this could be any data
    //Serial.print("send");
    oscUDP.send(msg, destination);
    //Serial.println("done");
  //wifiUDP.beginPacket(destinationIP, destinationPort);
 // msg.send(wifiUDP);
 // wifiUDP.endPacket();
}


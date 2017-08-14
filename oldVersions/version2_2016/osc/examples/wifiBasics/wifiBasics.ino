#include <OscUDPwifi.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCData.h>

WiFiUDP wifiUDP;
unsigned int listeningPort = 9999;

OscUDPwifi oscUDPwifi; 
NetAddress destination;

// The IP address of a computer you are trying to reach
IPAddress destinationIP(141, 117, 245, 84);
int destinationPort = 12000;

void setup() {
    Serial.begin(9600);
    
    WiFi.begin("SSID", "PASSWORD");
    // wait for wifi to connect
    Serial.print("[Connecting]: ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println(WiFi.localIP());
    
    // startUDP
    wifiUDP.begin(listeningPort);
    oscUDPwifi.begin(wifiUDP);  
    
    destination.set(destinationIP, destinationPort);
}

void loop()
{
   sendOscNet();
   delay(500);
   oscUDPwifi.listen();
}
// listen for All OSC messages here
void oscEvent(OscMessage & msg) {
    // route messages using the "plug" functionality
    // this example redirects messages called "/incoming" to myFunction (below) 
    msg.plug("/inComingAddresssPattern", myFunction);
}

void myFunction(OscMessage & msg) {
    // get the data out of the message 
    int data = msg.getInt(0);
 
}
// send OSC Internet messages
void sendOscNet() {
    OscMessage msg("/outGoingAddressPattern"); // this could be any pattern
    msg.add(8799); // any value
    oscUDPwifi.send(msg, destination);
}


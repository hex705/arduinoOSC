
// MESSAGE PROTOCOL OBJECT
#include <OscSerial.h>

// tile support libraries
#include <EthernetUdp.h>
#include <SPI.h>  

OscSerial oscSerial;
long timer;

void setup() {
  Serial.begin(9600);
  oscSerial.begin(Serial); 
  pinMode(13, OUTPUT);
}

void loop() {
  // send a message every 100 ms
  // avoid using delay() since it just blocks everything  
  long now = millis();
  if (now-timer > 100) {
    
    OscMessage msg("/helloFromArduino");
    msg.add(0); // <-- this could be any data 
    oscSerial.send(msg);       
    timer = now;
  }
  
  // important! 
  oscSerial.listen();
  
}

void oscEvent(OscMessage &m) { // *note the & before msg
  // receive a message 
  m.plug("/led", myFunction); 
}

void myFunction(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(13, LOW);
  if (value == 1) digitalWrite(13, HIGH);
}

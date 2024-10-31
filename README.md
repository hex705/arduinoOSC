# arduinoOSC

*arduinoOSC* is a fork of [OSCuino](https://github.com/CNMAT/OSC), an Open Sound Control library for Arduino and Teensy boards developed at CNMAT at the University of California, Berkeley.

It was developed primarily by Yotam Mann at CNMAT where OSC was invented.
It benefits from contributions from Adrian Freed, John MacCallum, Matt Wright and Andy Schmeder

## Why arduinoOSC?

This forks provides a simplified API, focused only on the Arduino platform. It also includes a complimentary Processing library to communicate with the Arduino using OSC over the Serial port. The library is built on the excellent OscP5 by Andreas Schlegel. Both are intended to be consistent with OscP5’s usage patterns and object names.

**Note** -- at some point (2013ish?), the original CNMAT repository changed its message syntax from *OscMessage* to *OSCMessage* ( OSC all caps).  This fork did not follow that convention as it supports a downstream tool.  You may need to change object names in various examples -- YMMV.

## Change Log

July 2024
**ESP32** support updated
  -- type of int across boards is an issue
  -- on 2024 it seems esp32 ( at least ada fruit feather) is ok with arduino 16 bit int and esp 32bit int.
  -- removed an ifndef around ints in oscdata.h and oscdata.cpp to ensure that ints compile on Uno and feather. commented in each file respectively.
  

August 2022 -
**ESP32** support added.
  Send and receive OSC via serial (UNO) and UDP (Adafruit Feather huzzah32) to Node (using https://github.com/colinbdclark/osc.js/) and to Processing V3.xx (does not yet work with P4.xx+)


## Folders:

*archive* -- contains two older version of the library and wrapper

*osc* -- current active version -- use this code -- details below

*processingAddOn* -- OscSerial.jar file that works with OSCP5 to facilitate comms between Arduino and Processing


## Installation:

*Install From .ZIP*

You can download this repository as .ZIP and then in Arduino, navigate to *Sketch-->Include Library--> Add .ZIP Library*


*Install Manually*

To install the Arduino library, simply copy the contents of the osc folder into your Arduino sketchbook’s libraries folder.

*Processing Library Add-on (Ver<3.xx)*

To install the Processing library (found in processingAddOn), first install OscP5 (either by downloading it or by using the Add Library menu). Then, navigate your the /libraries inside your sketchbook. Find the OscP5/library folder. Place OscSerial.jar into that folder, next to OscP5.jar.

When you are done, your OscP5 library folder should look like this

OscP5/
     examples/
     library/
         oscP5.jar
         OscSerial.jar

## Development
Project developed by David Bouchard and Steve Daniels.  

http://www.deadpixel.ca/arduino-osc/

http://www.deadpixel.ca/projects/tiles-that-talk/

http://spinningtheweb.org/projects/tiles.html

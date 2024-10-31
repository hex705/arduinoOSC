*serialAbstractionTest.pd* provides parsing support for messages sent using OSC.  

Upload *serialBasics.ino* to your arduino.  

Open *serialAbstractionTest.pd* and click devices.  YOU wil lsee list of devices connected -- select arduino of choice by index  (usually 3 on my computer).  You maty need to edit the *'3'* in the open object.

YOu should see dat arriving in the PD window. 

This patch assumes OSC formatted data is arriving and prints OSC configured data as outlet. 

Requires *serialOcs-helper.pd* abstraction this must be in the abstraction folder.  Restart of PD probably required?

The helper solves teh assumption by PD serial port that data arriving is ascii not raw binary.  I could not find a straigtht up conversion object that was current.(2024)

But then again i have not played with pd in a long time.

____

##2024 summer

###tested with:

serialOSC on UNO

serialOSC from Adafruit huzzah esp32 

(with esp32, floats must be declared float or suffixed with 'f' - eg  1.01f;)

only receive is tested. 




  
  


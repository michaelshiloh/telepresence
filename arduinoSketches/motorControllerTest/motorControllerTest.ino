/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo and Micro support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  stopBoth();
}

void loop() { // run over and over
  stopBoth();

  Serial.println("M1 forward");
  for (int speed = 64; speed <= 127; speed++) {
    mySerial.write(speed);
    delay(100);
  }
  stopM1();
  Serial.println("M1 reverse");
  for (int speed = 64; speed >= 0; speed--) {
    mySerial.write(speed);
    delay(100);
  }

  
  Serial.println("M2 forward");
  for (int speed = 192; speed <= 255; speed++) {
    mySerial.write(speed);
    delay(100);
  }
  stopM1();
  Serial.println("M2 reverse");
  for (int speed = 192; speed >= 0; speed--) {
    mySerial.write(speed);
    delay(100);
  }
  
  stopBoth();
  

}

void stopM1() {
  mySerial.write(64);
  delay(2000);
}

void stopM2() {
  mySerial.write(192);
  delay(2000);
}

void stopBoth() {
  mySerial.write((byte)0);
  delay(2000);
}

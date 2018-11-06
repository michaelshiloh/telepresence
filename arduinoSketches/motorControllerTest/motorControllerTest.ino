/*
	simple test to test using the software serial library
	to communicate with the motor controller

	based on "Software serial multple serial test"
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

	the motor controller is in simple serial mode so each command is one
	byte, no response from controller

*/
#include <SoftwareSerial.h>

// in fact, we only use tx since communicatoin is one way
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

	// Values between 1 and 127 control one motor, with 64 being stop
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

  
	// Values between 127 and 255 control the other  motor, with 192 being stop
  Serial.println("M2 forward");
  for (int speed = 192; speed <= 255; speed++) {
    mySerial.write(speed);
    delay(100);
  }
  stopM1();
  Serial.println("M2 reverse");
	// this is a bug; it should only go to 127 not zero
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

// a value of zero stops both motors
void stopBoth() {
  mySerial.write((byte)0);
  delay(2000);
}

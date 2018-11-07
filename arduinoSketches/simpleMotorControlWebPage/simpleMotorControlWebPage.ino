/*
  // first attempt at terribly simple web control of motors
  // based on software serial example (built-in to Arduino)
  // to communicate with motor controller and interaction engine
  // to communicate with rPi

  Modification log

  November 6 2018 - written by Michael Shiloh
	Basic proof of concept: pressing the "LED On" button on the web page
	turns on the motor, but there is a bug in that pressing "LED Off"
	causes both motors to stutter and not turn off. Also upon reset both
	motors stutter.

	oh i just noticed that pin 11 is used for both transmission and for
	a pushbutton (which is not used) which is probably causing conflict

*/

#include <SoftwareSerial.h>

SoftwareSerial softwareSerial(10, 11); // RX, TX

const int LEDPin = 13; // led that we will toggle

const int MYFORWARD = 0;
const int MYREVERSE = 1;

char inChar;  // character we will use for messages from the RPi


void setup() {

  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);

  softwareSerial.begin(9600);
  delay(100);
  softwareSerial.write((byte)0);

}

void loop() {
  // read the character we recieve on the serial port from the RPi
  if (Serial.available()) {
    inChar = (char)Serial.read();
  }

  // if we get a 'H', turn the LED on, else turn it off
  if (inChar == 'H') {
    digitalWrite(LEDPin, HIGH);

    // Serial.println("on");
    delay(300);
  } else if (inChar == 'F') {
    // Move forward fast
    moveForward (255);
    delay(300);
  } else if (inChar == 'W') {
    // Move forward slowly
    moveForward (50);
    delay(300);
  } else if (inChar == 'T') {
    // turn left
    turnLeft (50);
    delay(300);
  } else if (inChar == 'R') {
    // turn left
    turnRight (50);
    delay(300);
  } else if (inChar == 'S') {
    // Stop
    stopBothMotors ();
    delay(300);
  } else {
    digitalWrite(LEDPin, LOW);
    stopBothMotors();
  }
}

/*
   0 == stop
   1 = slow
*/
void moveForward(int speed) {
  controlMotor1(speed, MYFORWARD);
  controlMotor2(speed, MYFORWARD);
}

void turnLeft(int speed) {
  controlMotor1(speed, MYFORWARD);
  controlMotor2(speed, MYREVERSE);
}

void turnRight(int speed) {
  controlMotor1(speed, MYREVERSE);
  controlMotor2(speed, MYFORWARD);
}



/*    0 = stop
      1 = slowest
      1-63 = speed
    63-255 = full speed
*/

void controlMotor1(int speed, bool direction) {
  /*
     From the documentation:

     Sending a character between 1 and 127 will control
     motor 1. 1 is full reverse, 64 is stop and 127 is full forward.

     Character 0 (hex 0x00) is a special case.
     Sending this character will shut down both motors.
  */
  if (speed == 0) {
    softwareSerial.write(64);
  }

  if (direction == MYFORWARD) {
    speed = map(speed, 0, 255, 65, 127);
    speed = constrain(speed, 65, 127);
  } else {
    speed = map(speed, 0, 255, 63, 1);
    speed = constrain(speed, 1, 63);
  }
  
//  Serial.println("M1 speed = ");
//  Serial.println(speed);
  
  softwareSerial.write(speed);
}

void controlMotor2(int speed, bool direction) {
  /*
     From the documentation:


     Sending a character between 128 and 255 will control motor 2. 128
     is full reverse, 192 is stop and 255 is full forward.

     Character 0 (hex 0x00) is a special case.
     Sending this character will shut down both motors.
  */
  if (speed == 0) {
    softwareSerial.write(192);
  }

  if (direction == MYFORWARD) {
    speed = map(speed, 0, 255, 191, 128);
    speed = constrain(speed, 128, 191);
  } else {
    speed = map(speed, 0, 255, 193, 255);
    speed = constrain(speed, 193, 255);
  }
  
//  Serial.println("M2 speed = ");
//  Serial.println(speed);
  
  softwareSerial.write(speed);
}

void stopBothMotors() {
  softwareSerial.write((byte)0);
}

/*
  Very simple robot control using a single letter protocol
	over the hardware serial port. Motor controller is connected
	to a software serial port.

	Commands can come from any serial terminal such as the Arduino
	IDE built-in serial monitor, or from a program running on a
	Raspberry Pi (e.g. a web server for remote control)

  Modification log

  November 6 2018 - written by Michael Shiloh
	Basic proof of concept: pressing the "LED On" button on the web page
	turns on the motor, but there is a bug in that pressing "LED Off"
	causes both motors to stutter and not turn off. Also upon reset both
	motors stutter.

	Nov 9 2018 - Michael Shiloh
	implemented decent robot control

  Nov 10 2018 - Michael Shiloh
  Turn off motors after short delay so if web client disconnects
  robot doesn't keep moving

	Feb 22 2019 - Michael Shiloh
	add speed control

	Feb 15 2020 - Michael Shiloh
	moved transmit pin to free up PWM pins, but has not been tested
	Also I'm not 100% sure if the new pin is Tx or Rx, since I wasn't
	paying attention (only one pin is used since I never bothered 
	wiring up the other, probably Rx)

*/

#include <SoftwareSerial.h>

/* old
SoftwareSerial softwareSerial(10, 11); // RX, TX
*/
// new
SoftwareSerial softwareSerial(8, 12); // RX, TX

const int LEDPin = 13; // the built-in

const int MYFORWARD = 0;
const int MYREVERSE = 1;

int forwardSpeed = 80; 

char inChar;  // character we will use for messages from the RPi


void setup() {

  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);

  softwareSerial.begin(9600);
  delay(100);

  // stop the motors
  softwareSerial.write((byte)0);

}

void loop() {
  // read the character we receive on the serial port from the RPi
  if (Serial.available()) {
    inChar = (char)Serial.read();
    Serial.print("Arduino: received character");
    Serial.println(inChar);

    /*
      1 = pin 13 LED on
      0 = pin 13 LED  off
      F = move Forward
      B = move Backwards
      L = turn lEft
      R = turn rIght
      S = Stop
    	+ = set forward motor speed faster
    	- = set forward motor speed slower
    */

    switch (inChar) {

      case '1':
        Serial.println("Arduino: LED on");
        digitalWrite(LEDPin, HIGH);
        break;
      case '0':
        Serial.println("Arduino: LED off");
        digitalWrite(LEDPin, LOW);
        break;
      case 'F':
        moveForward (forwardSpeed);
        //delay(800);
        //stopBothMotors ();
        break;
      case 'B':
        moveBackwards(80);
        //delay(800);
        //stopBothMotors ();
        break;
      case 'L':
        turnLeft (80);
        //delay(500);
        //stopBothMotors ();
        break;
      case 'R':
        turnRight (80);
        //delay(500);
        //stopBothMotors ();
        break;
      case '+':
        faster ();
        //delay(500);
        //stopBothMotors ();
        break;
      case '-':
        slower ();
        //delay(500);
        //stopBothMotors ();
        break;
      default:
        stopBothMotors ();
    }
  }
}

/*
   0 == stop
   1 = slow
*/
void moveForward(int speed) {
  Serial.println("Arduino: moveForward");
  controlMotor1(speed, MYFORWARD);
  controlMotor2(speed, MYFORWARD);
}

void moveBackwards(int speed) {
  Serial.println("Arduino: moveBackwards");
  controlMotor1(speed, MYREVERSE);
  controlMotor2(speed, MYREVERSE);
}

void turnLeft(int speed) {
  Serial.println("Arduino: turnLeft");
  controlMotor1(speed, MYFORWARD);
  controlMotor2(speed, MYREVERSE);
}

void turnRight(int speed) {
  Serial.println("Arduino: turnRight");
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

  Serial.print("Arduino: M1 speed = ");
  Serial.println(speed);

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

  Serial.print("Arduino: M2 speed = ");
  Serial.println(speed);

  softwareSerial.write(speed);
}

void stopBothMotors() {
  Serial.println("Arduino: stopBothMotors");
  softwareSerial.write((byte)0);
}

void faster() {
  Serial.print("Arduino: faster: ");
	forwardSpeed+=10;
  Serial.print("Speed now at: ");
  Serial.println(forwardSpeed);
}

void slower() {
  Serial.println("Arduino: slower: ");
	forwardSpeed-=10;
  Serial.print("Speed now at: ");
  Serial.println(forwardSpeed);
}

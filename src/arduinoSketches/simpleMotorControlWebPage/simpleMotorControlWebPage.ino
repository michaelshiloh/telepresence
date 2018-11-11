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

	Nov 9 2018 - Michael Shiloh
	implemented decent robot control

  Nov 10 2018 - Michael Shiloh
  Turn off motors after short delay so if web client disconnects
  robot doesn't keep moving

*/

#include <SoftwareSerial.h>

SoftwareSerial softwareSerial(10, 11); // RX, TX

const int LEDPin = 13; // the built-in

const int MYFORWARD = 0;
const int MYREVERSE = 1;

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

    /*
      H = pin 13 LED on
      L = pin 13 LED  off
      F = move Forward
      R = move Reverse
      E = turn lEft
      I = turn rIght
      S = Stop
    */

    switch (inChar) {

      case 'H':
        digitalWrite(LEDPin, HIGH);
        break;
      case 'L':
        digitalWrite(LEDPin, LOW);
        break;
      case 'F':
        moveForward (80);
        //delay(800);
        //stopBothMotors ();
        break;
      case 'R':
        moveReverse (80);
        //delay(800);
        //stopBothMotors ();
        break;
      case 'E':
        turnLeft (80);
        //delay(500);
        //stopBothMotors ();
        break;
      case 'I':
        turnRight (80);
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
  controlMotor1(speed, MYFORWARD);
  controlMotor2(speed, MYFORWARD);
}

void moveReverse(int speed) {
  controlMotor1(speed, MYREVERSE);
  controlMotor2(speed, MYREVERSE);
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

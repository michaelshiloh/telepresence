#include <SoftwareSerial.h>

SoftwareSerial softwareSerial(10, 11); // RX, TX

int led = 13; // led that we will toggle
char inChar;  // character we will use for messages from the RPi

int button = 11;
int buttonState;

void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);

  softwareSerial.begin(9600);
  delay(100);
  softwareSerial.write((byte)0);
  softwareSerial.write((byte)0);
  softwareSerial.write((byte)0);
  softwareSerial.write((byte)0);
  softwareSerial.write((byte)0);
  softwareSerial.write((byte)0);
}

void loop() {
  // read the character we recieve on the serial port from the RPi
  if (Serial.available()) {
    inChar = (char)Serial.read();
  }

  // if we get a 'H', turn the LED on, else turn it off
  if (inChar == 'H') {
    digitalWrite(led, HIGH);
    softwareSerial.write(10);
    softwareSerial.write(240);
  }
  else {
    digitalWrite(led, LOW);
    softwareSerial.write((byte)0);
  }

  // Button event checker - if pressed, send message to RPi
  int newState = digitalRead(button);
  if (buttonState != newState) {
    buttonState = newState;
    if (buttonState == HIGH) {
      Serial.println("light");
    }
    else {
      Serial.println("dark");
    }
  }
}

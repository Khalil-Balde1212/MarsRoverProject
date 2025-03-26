#include <Adafruit_PWMServoDriver.h>
#include "chassis.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// psd
const byte interruptPin = 3; // PSD interrupt pin
volatile byte state = HIGH;  // sets interrupt to HIGH intially
// current
const byte currentPin = A1;   // current sensor input pin
const float Vreference = 5.0; // arduino internal reference voltage
const float volts_per_amp = 0.2f;
const float offsetV = 0;         // offset voltage
const float sensitivity = 0.185; // current sensor sensitivity
float currentSensorValue = 0;    // reads the value from the current sensor
// photo
const byte photoPin = A0; // photo sensor input pin
float photoValue = 0;     // to read photo value

// joystick setup, directional values and pushbutton pin
int up = 0;
int down = 0;
int right = 0;
int left = 0;
int autom = 5;

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(interruptPin, INPUT);
  pinMode(currentPin, INPUT);
  pinMode(photoPin, INPUT);
  pinMode(autom, INPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin), psdInterrupt, FALLING);
}

void psdInterrupt()
{
  stopm();
  Serial.println("interrupted");
  volatile byte state = HIGH;
}

float readCurrent()
{
  currentSensorValue = analogRead(currentPin);
  float voltage = currentSensorValue * (Vreference / 1023.0); // Convert analog value to voltage
  voltage -= 2.5;
  float current = voltage / volts_per_amp;
  return current;
}

void readPhoto()
{
  int value = analogRead(photoPin);
  if (value > 30)
    stopm();
}

void loop()
{
  int steer = analogRead(A2);
  int drive = analogRead(A3);
  float mappedSteer = map(steer, 0, 255, -1, 1);
  float mappedDrive = map(drive, 0, 255, -1, 1);

  setDifferentialSpeeds(drive + steer, drive - steer);
}

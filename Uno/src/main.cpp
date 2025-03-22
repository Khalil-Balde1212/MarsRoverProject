#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <psdISR.h>

#include "robot_const.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  65 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  465 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servonum = 0; //sets the PCA9685 channel for servo control

//psd
const byte interruptPin = 3;  //PSD interrupt pin
volatile byte state = HIGH; //sets interrupt to HIGH intially
//current
const byte currentPin = A1; //current sensor input pin
const float Vreference = 5; //arduino internal reference voltage
const float offsetV = 0;  //offset voltage
const float sensitivity = 0;  //current sensor sensitivity
float currentSensorValue = 0; //reads the value from the current sensor
//photo
const byte photoPin = A2; //photo sensor input pin
float photoValue = 0; //to read photo value


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); //TODO check for better frequencies
  //believe 50 is the standard
  pwm.setOscillatorFrequency(27000000); //shouldn't change anything as 27Mhz should be the original setting
  Serial.println("init PWM Servo Driver");

  pinMode(interruptPin, INPUT);
  pinMode(currentPin, INPUT);
  pinMode(photoPin, INPUT);
  //interrupt for PSD distance sensor at 10cm using 9.1k and 1k resistors for R2 and R1 respectively
  attachInterrupt(digitalPinToInterrupt(interruptPin), psdInterrupt, FALLING);


  Wire.setClock(400000); // 400kHz I2C clock
  Wire.begin();

}

void loop() {
  //turn off motors when it is dark
  while(photoSens != 0) { //replace with appropriate while condition
    //set motors to zero
  }

  //current checker, where is it going?
  currentSensorValue = analogRead(currentPin);
  float currentVoltage = currentSensorValue * (Vreference / 1023.0);
  float current = (currentVoltage - offsetV) / sensitivity;
  if(current <= 0.2) {

    //do something and set proper if statement value

  }

  //photo sensor to turn off when dark
  photoValue = analogRead(photoPin);
  if(photoValue < 250) {  //whatever value we want
    //set all motors to 0
    for(int i = 0; i < 6; i++) {
      pwm.writeMicroseconds(i, 500);
    }
  }

  //code to just turn the servo 
  Serial.println(servonum);
  pwm.writeMicroseconds(servonum, 500);
  delay(1000);
  pwm.writeMicroseconds(servonum, 2500);
  delay(1000);
  //delete or replace when more servo controls are added

  Serial.println("forward");
  pwm.setPWM(0, 0, 4095);
  pwm.setPWM(FL_MOTORA, 0, 4095);
  pwm.setPWM(FL_MOTORB, 0, 0);
  delay(1000);

  Serial.println("backward");
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(FL_MOTORA, 0, 0);
  pwm.setPWM(FL_MOTORB, 0, 4095);
  delay(1000);
}
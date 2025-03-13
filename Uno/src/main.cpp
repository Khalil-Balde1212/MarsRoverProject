#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#include "robot_const.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  65 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  465 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servonum = 0; //sets the PCA9685 channel for servo control

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); //TODO check for better frequencies
  //believe 50 is the standard
  pwm.setOscillatorFrequency(27000000); //shouldn't change anything as 27Mhz should be the original setting
  Serial.println("init PWM Servo Driver");


  Wire.setClock(400000); // 400kHz I2C clock
  Wire.begin();


}

void loop() {
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
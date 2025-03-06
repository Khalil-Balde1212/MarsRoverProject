#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#include "robot_const.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(800); //TODO check for better frequencies
  Serial.println("init PWM Servo Driver");


  Wire.setClock(400000); // 400kHz I2C clock
  Wire.begin();


}

void loop() {
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
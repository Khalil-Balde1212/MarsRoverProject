#include <Arduino.h>

#define MOTOR_PIN1 A0
#define MOTOR_PIN2 A1
#define MOTOR_PIN3 A2
#define MOTOR_PIN4 A4

/**
 * Some speed between -1 and 1
 */
void runMotor(double speed){
  //clamp input
  if (speed > 1) {
    speed = 1;
  } else if (speed < -1) {
    speed = -1;
  }
  
  if(speed > 0){
    analogWrite(MOTOR_PIN1, 255 * speed);
    analogWrite(MOTOR_PIN2, 0);
  } else {
    analogWrite(MOTOR_PIN1, 0);
    analogWrite(MOTOR_PIN2, 255 * -speed);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  runMotor(0.5);
  delay(1000);
  runMotor(-0.5);
  delay(1000);
}

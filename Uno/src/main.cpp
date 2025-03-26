#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include "robot_const.h"

#include <Servo.h>

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
const float Vreference = 5.0; //arduino internal reference voltage
const float volts_per_amp = 0.2f;
const float offsetV = 0;  //offset voltage
const float sensitivity = 0.185;  //current sensor sensitivity
float currentSensorValue = 0; //reads the value from the current sensor
//photo
const byte photoPin = A0; //photo sensor input pin
float photoValue = 0; //to read photo value

Servo Servo1; 

void setup() {
  Serial.println("setup");
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  pinMode(currentPin, INPUT);
  pinMode(photoPin, INPUT);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); //TODO check for better frequencies
  //believe 50 is the standard
  pwm.setOscillatorFrequency(27000000); //shouldn't change anything as 27Mhz should be the original setting
  Servo1.attach(10); 
  Serial.println("init PWM Servo Driver");
  
  //interrupt for PSD distance sensor at 10cm using 9.1k and 1k resistors for R2 and R1 respectively
  attachInterrupt(digitalPinToInterrupt(interruptPin), psdInterrupt, FALLING);


  Wire.setClock(400000); // 400kHz I2C clock
  Wire.begin();
}

void psdInterrupt() {
  //set all motors to 0
  Serial.println("interrupted");
  volatile byte state = HIGH;
}

void printCurrent(){
  Serial.print("Current: ");
  Serial.print(readCurrent());
  Serial.println(" A");
}

float readCurrent(){
  currentSensorValue = analogRead(currentPin);
  float voltage = currentSensorValue * (Vreference/1023.0); // Convert analog value to voltage
  voltage -= 2.5;
  float current = voltage/volts_per_amp;
  return current;
}
void loop() {
  //Serial.println("running");
  delay(150);
  printCurrent();

  Servo1.write(0); 
  delay(1000); 
  // Make servo go to 90 degrees 
  Servo1.write(90); 
  delay(1000); 
  // Make servo go to 180 degrees 
  Servo1.write(180); 
  delay(1000);

  /*
  Serial.println("why");
  pwm.setPWM(10, 0, 4095);
  delay(1000);
  //pwm.writeMicroseconds(servonum, 2500);
  pwm.setPWM(10, 4095, 0);
  delay(1000);
  */
  
  int  value = analogRead(photoPin);
  if (value > 30)
  {
    Serial.println("high");
    //run rover as normal
  }
  else{
    Serial.println("low");
    //stop rover motion
  }
}
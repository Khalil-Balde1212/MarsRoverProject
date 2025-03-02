#include <Arduino.h>
#include "psdISR.h"
#include "encoders.h"

// put function declarations here:
const int pwm = 1;
const int in_1 = 2;
const int in_2 = 3;
int psdRead = 0;  //PSD read input in Volts
float psdDist = 0;  //psd value in cm

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(5, 10);
  //PSD interrupt
  attachInterrupt(digitalPinToInterrupt(2), psdInterrupt, CHANGE);

  Serial.begin(9600);
  pinMode(4,INPUT);
  pinMode(7,INPUT);
  pinMode(1,OUTPUT);
  //pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2, INPUT); //PSD input
}

void loop() {
  Serial.println(digitalRead(4));
  digitalWrite(in_1, HIGH);
  digitalWrite(in_2, LOW);
  analogWrite(pwm, 255);
  // put your main code here, to run repeatedly:
}

//PSD fucntion, input V and convert to cm to output
float psdMath() {
  psdRead = analogRead(2);
  psdDist = 4800/(psdRead - 20);
  Serial.println(psdRead);
  Serial.println(psdDist);
  return(psdDist);
  //delay(1500);  
}
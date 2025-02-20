#include <Arduino.h>
#include <servo.h>
// put function declarations here:
int myFunction(int, int);
const int pwm = 1;
const int in_1 = 2;
const int in_2 = 3;

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(5, 10);
  Serial.begin(9600);
  pinMode(4,INPUT);
  pinMode(7,INPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  Serial.println(digitalRead(4));
  digitalWrite(in_1, HIGH);
  digitalWrite(in_2, LOW);
  analogWrite(pwm, 255);
  // put your main code here, to run repeatedly:
}

/* put function definitions here:
int myFunction(int x, int y) {
  return x * y;
}*/
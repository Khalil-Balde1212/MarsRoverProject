#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(5, 10);
  Serial.begin(9600);
}

void loop() {
  Serial.println("YOHOHOHO");
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x * y;
}
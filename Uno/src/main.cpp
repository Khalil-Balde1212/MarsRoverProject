#include <Arduino.h>
#include "psdISR.h"
#include "encoders.h"

void setup() {
  //Encoder setup
  encoders::initEncoders();
}

void loop() {
  encoders::encoderCounts[0];
}
#include <psdISR.h>
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

//PSD interrupt code if distance is less than 10cm
//use voltage divider so that if pin input becomes 'LOW' it triggers interrupt
void psdInterrupt() {
    //stuff to make cpp work?, it's late
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
  //set all motors to 0
  for(int i = 0; i < 6; i++) {
    pwm.writeMicroseconds(i, 500);
  }
  delay(250);
  //turns pin 3 back to HIGH
  volatile byte state = HIGH;
}

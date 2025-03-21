#include <psdISR.h>
 
//PSD interrupt code if distance is less than 10cm
//use voltage divider so that if pin input becomes 'LOW' it triggers interrupt
void psdInterrupt() {
  //set all motors to 0

  //turns pin 3 back to HIGH
  volatile byte state = HIGH;
}

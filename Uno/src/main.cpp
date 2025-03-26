#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//motor pins front/back/middle, left/right and forward/back
const int FLF = 8;
const int FLR = 9;
const int FRF = 7;
const int FRR = 6;
const int BLF = 12;
const int BLR = 13;
const int BRF = 5;
const int BRR = 4;
const int MLF = 14;
const int MLR = 15;
const int MRF = 11;
const int MRR = 10;
const int motorSpeed = 4095;

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

//joystick setup, directional values and pushbutton pin
int up = 0;
int down = 0;
int right = 0;
int left = 0;
int autom = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(interruptPin, INPUT);
  pinMode(currentPin, INPUT);
  pinMode(photoPin, INPUT);
  pinMode(autom, INPUT);
  
  pwm.begin();
  pwm.setPWMFreq(50); //TODO check for better frequencies
  //believe 50 is the standard
  pwm.setOscillatorFrequency(27000000); //shouldn't change anything as 27Mhz should be the original setting 
  Serial.println("init PWM Servo Driver");

  for (int i=0; i < 16; i++) {
    //pinMode(i, 0);
    Serial.println(i);
    pwm.setPWM(i, 0, 0);
  }
  attachInterrupt(digitalPinToInterrupt(interruptPin), psdInterrupt, FALLING);
}

void psdInterrupt() {
  stopm();
  Serial.println("interrupted");
  volatile byte state = HIGH;
}

void forward() {
  Serial.println("forward");
  pwm.setPWM(FLF, 0, motorSpeed);
  pwm.setPWM(FLR, 0, 0);
  pwm.setPWM(FRF, 0, motorSpeed);
  pwm.setPWM(FRR, 0, 0);
  pwm.setPWM(BLF, 0, motorSpeed);
  pwm.setPWM(BLR, 0, 0);
  pwm.setPWM(BRF, 0, motorSpeed);
  pwm.setPWM(BRR, 0, 0);
  pwm.setPWM(MLF, 0, motorSpeed);
  pwm.setPWM(MLR, 0, 0);
  pwm.setPWM(MRF, 0, motorSpeed);
  pwm.setPWM(MRR, 0, 0);
}

void reverse() {
  Serial.println("reverse");
  pwm.setPWM(FLF, 0, 0);
  pwm.setPWM(FLR, 0, motorSpeed);
  pwm.setPWM(FRF, 0, 0);
  pwm.setPWM(FRR, 0, motorSpeed);
  pwm.setPWM(BLF, 0, 0);
  pwm.setPWM(BLR, 0, motorSpeed);
  pwm.setPWM(BRF, 0, 0);
  pwm.setPWM(BRR, 0, motorSpeed);
  pwm.setPWM(MLF, 0, 0);
  pwm.setPWM(MLR, 0, motorSpeed);
  pwm.setPWM(MRF, 0, 0);
  pwm.setPWM(MRR, 0, motorSpeed);
}

void leftm() {
  Serial.println("left");
  pwm.setPWM(FLF, 0, 0);
  pwm.setPWM(FLR, 0, motorSpeed);
  pwm.setPWM(FRF, 0, motorSpeed);
  pwm.setPWM(FRR, 0, 0);
  pwm.setPWM(BLF, 0, 0);
  pwm.setPWM(BLR, 0, motorSpeed);
  pwm.setPWM(BRF, 0, motorSpeed);
  pwm.setPWM(BRR, 0, 0);
  pwm.setPWM(MLF, 0, 0);
  pwm.setPWM(MLR, 0, motorSpeed);
  pwm.setPWM(MRF, 0, motorSpeed);
  pwm.setPWM(MRR, 0, 0);
}

void rightm(){
  Serial.println("right");
  pwm.setPWM(FLF, 0, motorSpeed);
  pwm.setPWM(FLR, 0, 0);
  pwm.setPWM(FRF, 0, 0);
  pwm.setPWM(FRR, 0, motorSpeed);
  pwm.setPWM(BLF, 0, motorSpeed);
  pwm.setPWM(BLR, 0, 0);
  pwm.setPWM(BRF, 0, 0);
  pwm.setPWM(BRR, 0, motorSpeed);
  pwm.setPWM(MLF, 0, motorSpeed);
  pwm.setPWM(MLR, 0, 0);
  pwm.setPWM(MRF, 0, 0);
  pwm.setPWM(MRR, 0, motorSpeed);
}

void stopm() {
  Serial.println("stop");
  pwm.setPWM(FLF, 0, motorSpeed);
  pwm.setPWM(FLR, 0, motorSpeed);
  pwm.setPWM(FRF, 0, motorSpeed);
  pwm.setPWM(FRR, 0, motorSpeed);
  pwm.setPWM(BLF, 0, motorSpeed);
  pwm.setPWM(BLR, 0, motorSpeed);
  pwm.setPWM(BRF, 0, motorSpeed);
  pwm.setPWM(BRR, 0, motorSpeed);
  pwm.setPWM(MLF, 0, motorSpeed);
  pwm.setPWM(MLR, 0, motorSpeed);
  pwm.setPWM(MRF, 0, motorSpeed);
  pwm.setPWM(MRR, 0, motorSpeed);
}

float readCurrent(){
  currentSensorValue = analogRead(currentPin);
  float voltage = currentSensorValue * (Vreference/1023.0); // Convert analog value to voltage
  voltage -= 2.5;
  float current = voltage/volts_per_amp;
  return current;
}

void readPhoto() {
  int  value = analogRead(photoPin);
  if (value > 30)
    stopm();
  }
}

void loop() {
  readPhoto();
  //readCurrent();
  //Serial.println("The Current draw on the motor is: "
  //Serial.print(current);

  int Xm = analogRead(A2);
  int Ym = analogRead(A3);

  //joystick setup
  up = 0;
  down = 0;
  right = 0;
  left = 0;
  
  if(Xm <= 450) {
    up = map(Xm, 450, 0, 500, 4095);
  }
  else if(Xm > 550) {
    down = map(Xm, 550, 1021, 500, 4095);
  }
  else if(Ym <= 450) {
    right = map(Ym, 450, 0, 500, 4095);
  }
  else if(Ym > 550) {
    left = map(Ym, 550, 1021, 500, 4095);
  }

  String p1 = "Xm =" +String(Xm)+ " - Ym =" +String(Ym);
  String p2 = "UP =" +String(up)+ " - DOWN =" + String(down)+ " - RIGHT =" + String(right)+" - LEFT =" +String(left);
 

  if (autom == HIGH) {
    forward();
  }else if (down > 50) {
    forward();
  }else if (up > 50) {
    reverse();
  }else if (left > 50) {
    rightm();
  } else if (right > 50) {
    leftm();
  }
  else {
    stopm();
  }

  //Serial.println(p1);
  //Serial.println(p2);
  
}

#include <Adafruit_PWMServoDriver.h>
#include "chassis.h"

#define ALPHA 0.7  // Smoothing factor for exponential moving average

float prevSteerEMA = 0;
float prevDriveEMA = 0;
float filteredSteer = 0;
float filteredDrive = 0;

void applyExponentialMovingAverageFilter();

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");

  initChassis();
}

void loop()
{
  applyExponentialMovingAverageFilter();
  float mappedSteer = (filteredSteer / 1023.0f) * 2.0f - 1.0f;
  float mappedDrive = (filteredDrive / 1023.0f) * 2.0f - 1.0f;

  float leftSpeed = mappedDrive + mappedSteer;
  float rightSpeed = mappedDrive - mappedSteer;

  // Normalize speeds to avoid conflicting directions
  float maxMagnitude = max(abs(leftSpeed), abs(rightSpeed));
  if (maxMagnitude > 1.0f) {
    leftSpeed /= maxMagnitude;
    rightSpeed /= maxMagnitude;
  }

  setDifferentialSpeeds(leftSpeed, rightSpeed);
}

void applyExponentialMovingAverageFilter() {
  float rawSteer = analogRead(A3);
  float rawDrive = analogRead(A2);

  // Apply exponential moving average
  filteredSteer = prevSteerEMA + ALPHA*(rawSteer - prevSteerEMA);
  filteredDrive = prevDriveEMA + ALPHA*(rawDrive - prevDriveEMA);

  // Update previous EMA values
  prevSteerEMA = filteredSteer;
  prevDriveEMA = filteredDrive;

  // Serial.print("Steer: ");Serial.print(filteredSteer);Serial.print("\tDrive: ");Serial.println(filteredDrive);
}

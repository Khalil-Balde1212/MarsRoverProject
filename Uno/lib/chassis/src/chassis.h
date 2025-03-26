#ifndef CHASSIS_H
#define CHASSIS_H

void initChassis();
void setSpeed(int forward, int reverse, double speed);

void setSpeedFL(double speed);
void setSpeedCL(double speed);
void setSpeedBL(double speed);

void setSpeedFR(double speed);
void setSpeedBR(double speed);
void setSpeedCR(double speed);

void setDifferentialSpeeds(double leftSpeed, double rightSpeed);

#endif
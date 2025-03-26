#include <Adafruit_PWMServoDriver.h>
#include "chassis.h"
#include "robot_const.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

setSpeed(int forward, int reverse, double speed)
{
    if (speed > 0)
    { //forward
        pwm.setPWM(forward, 0, speed);
        pwm.setPWM(reverse, 0, 0);
    }
    else
    {//reverse or coast
        pwm.setPWM(forward, 0, 0);
        pwm.setPWM(reverse, 0, speed);
    }
}

setSpeedFL(double speed)
{
    setSpeed(FL_MOTORA, FL_MOTORB, speed);
}

setSpeedCL(double speed)
{
    setSpeed(CL_MOTORA, CL_MOTORB, speed);
}

setSpeedBL(double speed)
{
    setSpeed(BL_MOTORA, BL_MOTORB, speed);
}

setSpeedFR(double speed)
{
    setSpeed(FR_MOTORA, FR_MOTORB, speed);
}

setSpeedCR(double speed)
{
    setSpeed(CR_MOTORA, CR_MOTORB, speed);
}

setSpeedBR(double speed)
{
    setSpeed(BR_MOTORA, BR_MOTORB, speed);
}

setDifferentialSpeeds(double leftSpeed, double rightSpeed)
{
    setSpeedFL(leftSpeed);
    setSpeedCL(leftSpeed);
    setSpeedBL(leftSpeed);

    setSpeedFR(rightSpeed);
    setSpeedCR(rightSpeed);
    setSpeedBR(rightSpeed);
}
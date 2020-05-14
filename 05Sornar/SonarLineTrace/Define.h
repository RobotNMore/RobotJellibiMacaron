#ifndef __DEFINE_H__
#define __DEFINE_H__
#include <Arduino.h>


#define SERVO_LEFT_ANGLE 20
#define SERVO_MIDDLE_ANGLE 70
#define SERVO_RIGHT_ANGLE 120

#define MAX_PWM 255
#define HIGH_PWM 120
#define LOW_PWM  60
#define MIN_PWM 0

#define NORMAL_DRIVE_SPEED 65

#define LINEDETECT_THRESHOLD_MIN 700
#define BLANKDETECT_THERSHOLD_MAX 500

#define TURN_INITIAL_WHEEL_SPEED 90
#define TURN_INSIDE_WHEEL_SPEED  40
#define TURN_OUTSIDE_WHEEL_SPEED 90


static const uint8_t s_RightWheelPWM = 6;
static const uint8_t s_LeftWheelPWM = 5;
static const uint8_t s_RightWheelDir = 8;
static const uint8_t s_LeftWheelDir = 7;
static const uint8_t s_SensorBottomRight = A7;
static const uint8_t s_SensorBottomLeft = A6;
static const uint8_t s_Servo = 9;
static const uint8_t s_Trig  = 13;
static const uint8_t s_Echo  = 12;



#endif//__DEFINE_H__

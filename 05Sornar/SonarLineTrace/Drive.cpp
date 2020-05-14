#include "Drive.h"
#include <Arduino.h>
#include "Define.h"


void Drive::Init()
{
    pinMode(_rightWheelDir, OUTPUT);
    pinMode(_leftWheelDir, OUTPUT);
    pinMode(_rightWheelPwm, OUTPUT);
    pinMode(_leftWheelPwm, OUTPUT);
    pinMode(_pinBottomRight, INPUT);
    pinMode(_pinBottomLeft, INPUT);

}
void Drive::InitSensor() 
{
    Stop();
    _centerValue = GetRight() - GetLeft();
}

void Drive::Sensing()
{
    _rightValue = GetRight();
    _leftValue = GetLeft();
}



void Drive::Stop() 
{
    analogWrite(_leftWheelPwm, 0);
    analogWrite(_rightWheelPwm, 0);
}


int Drive::LineTrace() 
{
    int16_t turnSpeed = ((_rightValue-_leftValue) - _centerValue)/12;
    int16_t leftSpeed = Speed + turnSpeed;
    int16_t rightSpeed = Speed - turnSpeed;

    digitalWrite( _leftWheelDir, (leftSpeed > 0)?1:0);
    digitalWrite( _rightWheelDir, (rightSpeed > 0)?0:1);
    analogWrite( _leftWheelPwm, round(abs(leftSpeed)));
    analogWrite( _rightWheelPwm, round(abs(rightSpeed)));
    
    int servoAngle = SERVO_MIDDLE_ANGLE - turnSpeed;
    if(servoAngle>SERVO_RIGHT_ANGLE) servoAngle = SERVO_RIGHT_ANGLE;
    else if(servoAngle<SERVO_LEFT_ANGLE) servoAngle = SERVO_LEFT_ANGLE;
    
    if(_sonarCon.SonarRead() < 7){
      Stop();
      delay(600);
    }
    return servoAngle;

}


int16_t Drive::GetLeft() 
{
    return analogRead(_pinBottomLeft);
}

int16_t Drive::GetRight() 
{
    return analogRead(_pinBottomRight);
}

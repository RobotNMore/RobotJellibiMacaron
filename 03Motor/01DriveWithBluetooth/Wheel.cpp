#include "Wheel.h"

Wheel::Wheel()
: _pwmPin(0)
, _dirPin(0)
, _bRightWheel(true)
{
}

void Wheel::Init(int pwmPin, int dirPin, bool bRightWheel) 
{
    _pwmPin = pwmPin;
    _dirPin = dirPin;
    _bRightWheel = bRightWheel;
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    Stop();
}
void Wheel::Stop()
{
    analogWrite(_pwmPin, _STOP_PWM_);
}
void Wheel::ForwardL()
{
    digitalWrite(_dirPin, (_bRightWheel)?LOW:HIGH);
    analogWrite(_pwmPin, _LOWSPEED_PWM_);    
}
void Wheel::ForwardH()
{
    digitalWrite(_dirPin, (_bRightWheel)?LOW:HIGH);
    analogWrite(_pwmPin, _DEFSPEED_PWM_);
}
void Wheel::BackwardL()
{
    digitalWrite(_dirPin, (_bRightWheel)?HIGH:LOW);
    analogWrite(_pwmPin, _LOWSPEED_PWM_);    
}
void Wheel::BackwardH()
{
    digitalWrite(_dirPin, (_bRightWheel)?HIGH:LOW);
    analogWrite(_pwmPin, _DEFSPEED_PWM_);    
}  


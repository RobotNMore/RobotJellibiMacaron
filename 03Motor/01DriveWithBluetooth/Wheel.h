#ifndef __WHEEL_H__
#define __WHEEL_H__
#include <arduino.h>

class Wheel
{
private:
  int _pwmPin;
  int _dirPin;
  bool _bRightWheel;
  const int _STOP_PWM_ = 0;
  const int _LOWSPEED_PWM_ = 50;
  const int _DEFSPEED_PWM_ = 150;
  
public:
  Wheel();
  void Init(int pwmPin, int dirPin, bool bRightWheel);
  void Stop();  
  void ForwardL();
  void ForwardH();
  void BackwardL();
  void BackwardH();
};

#endif//__WHEEL_H__
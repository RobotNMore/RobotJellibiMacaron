#ifndef __DRIVE_H__
#define __DRIVE_H__
#include <Arduino.h>

#include "Define.h"
#include "SonarControl.h"



class Drive
{
private: 
    uint8_t _rightWheelPwm;
    uint8_t _rightWheelDir;
    uint8_t _leftWheelPwm;
    uint8_t _leftWheelDir;
    uint8_t _pinBottomRight;
    uint8_t _pinBottomLeft; 

    int16_t  _rightValue;    
    int16_t  _leftValue; 
    int16_t  _centerValue;


public:

   Drive(){
     _rightWheelPwm = s_RightWheelPWM;
     _rightWheelDir = s_RightWheelDir;
     _leftWheelPwm = s_LeftWheelPWM;
     _leftWheelDir = s_LeftWheelDir;
     _pinBottomRight = s_SensorBottomRight;
     _pinBottomLeft = s_SensorBottomLeft;
   }


    
   int Speed = NORMAL_DRIVE_SPEED;

   SonarControl _sonarCon;
   
   void Init();
   void InitSensor();
   void Sensing();
   
   void Stop();
   int LineTrace();

   int16_t GetLeft();
   int16_t GetRight();
    
};

#endif//__DRIVE_H__

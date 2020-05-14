#ifndef __SONARCONTROL_H__
#define __SONARCONTROL_H__
#include <Arduino.h>
#include <Servo.h>

#include "Define.h"

class SonarControl
{
private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    uint8_t _servoPin;
public:
    SonarControl(){
      _trigPin = s_Trig;
      _echoPin = s_Echo;
      _servoPin = s_Servo;
    }
    Servo _servo;
    void Init();
    float SonarRead();
    void ServoWrite(int n);
    

};

#endif//__SORNARCONTROL_H__

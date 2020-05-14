#ifndef __DRIVE_H__
#define __DRIVE_H__
#include "Wheel.h"

class Drive
{
private:
    enum {
        DSTATE_STOP = 0, 
        DSTATE_FORWARD, 
        DSTATE_BACKWARD
    } _eDriveState;
    enum {
        TSTATE_NONE,
        TSTATE_RIGHT, 
        TSTATE_LEFT, 
    } _eTurnState;

    Wheel _rightWheel;
    Wheel _leftWheel;  
public:
    Drive();
    void Init(int rightPwmPin, 
              int rightDirPin, 
              int leftPmwPin, 
              int leftDirPin);
    void Stop();
    void Go();  
    void Back();
    void Left();
    void Right();
};

#endif//__DRIVE_H__
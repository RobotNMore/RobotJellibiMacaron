#include "Drive.h"

Drive::Drive()
: _eDriveState(DSTATE_STOP)
, _eTurnState(TSTATE_NONE)
{  
}

void Drive::Init(int rightPwmPin, 
                 int rightDirPin, 
                 int leftPmwPin, 
                 int leftDirPin)
{
    _rightWheel.Init(rightPwmPin, 
                     rightDirPin, true);
    _leftWheel.Init(leftPmwPin, 
                    leftDirPin, false);
    Stop();
}

void Drive::Stop()
{
    _rightWheel.Stop();
    _leftWheel.Stop();
    _eDriveState = DSTATE_STOP;
    _eTurnState = TSTATE_NONE;
}

void Drive::Go()
{
    if (_eDriveState == DSTATE_BACKWARD) {
        Stop();
    } else {
        _rightWheel.ForwardH();
        _leftWheel.ForwardH();
        _eDriveState = DSTATE_FORWARD;
        _eTurnState = TSTATE_NONE;
    }
}

void Drive::Back()
{
    if (_eDriveState == DSTATE_FORWARD) {
        Stop();
    } else {
        _rightWheel.BackwardH();
        _leftWheel.BackwardH();
        _eDriveState = DSTATE_BACKWARD;
        _eTurnState = TSTATE_NONE;
    }
}

void Drive::Left()
{
    switch(_eDriveState) {
        case DSTATE_STOP:
            _leftWheel.BackwardL();
            _rightWheel.ForwardL();
            _eTurnState = TSTATE_LEFT;
        break;
        case DSTATE_FORWARD:
        case DSTATE_BACKWARD:
            if (_eTurnState == TSTATE_NONE)
            {
                _leftWheel.ForwardL();
                _eTurnState = TSTATE_LEFT;
            } 
            else if (_eTurnState == TSTATE_RIGHT)
            {
                _leftWheel.ForwardH();
                _rightWheel.ForwardH();
                _eTurnState = TSTATE_NONE;
            }
        break;
    }
}
void Drive::Right()
{
    switch (_eDriveState) {
        case DSTATE_STOP:
            _rightWheel.BackwardL();
            _leftWheel.ForwardL();
            _eTurnState = TSTATE_RIGHT;
        break;
        case DSTATE_FORWARD:
        case DSTATE_BACKWARD:
            if (_eTurnState == TSTATE_NONE)
            {
                _rightWheel.ForwardL();
                _eTurnState = TSTATE_RIGHT;
            } 
            else if (_eTurnState == TSTATE_LEFT)
            {
                _leftWheel.ForwardH();
                _rightWheel.ForwardH();
                _eTurnState = TSTATE_NONE;
            }
        break;
    }
}



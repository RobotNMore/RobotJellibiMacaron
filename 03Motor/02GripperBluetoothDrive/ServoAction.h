#ifndef __SERVO_ACTION_H__
#define __SERVO_ACTION_H__
#include <arduino.h>

#include <Servo.h>
class ServoAction
{
private:
  const int _GRIP_PIN_ = 9; // SERVO 01 포트에 연결 된 핀(포트)
  const int _LIFT_PIN_ = 2; // SERVO 02 포트에 연결 된 핀(포트)
  
  Servo _servoGrip;
  Servo _servoLift;
  
  enum ESTATE{
    STATE_GRIP = 0,
    STATE_OPENGRIP, 
    STATE_LIFTGRIP 
  } _eState;
  
  bool StateMachine(ESTATE eNextState);
  
public:
  ServoAction();
  
  void Init();
  void OpenGrip();
  void Grip();
  void LiftGrip();
};

#endif//__SERVO_ACTION_H__
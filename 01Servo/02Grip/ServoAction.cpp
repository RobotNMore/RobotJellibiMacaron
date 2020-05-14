#include "ServoAction.h"
ServoAction::ServoAction()
{
}

void ServoAction::Init()
{
  _servoGrip.attach(_GRIP_PIN_);
  _servoLift.attach(_LIFT_PIN_);
  Grip();
  _eState = STATE_GRIP;
}
void ServoAction::OpenGrip()
{
  if (StateMachine(STATE_OPENGRIP)) {
    _servoGrip.write(0);
    _servoLift.write(10);
    _eState  = STATE_OPENGRIP;
  }
}

void ServoAction::Grip()
{
  if (StateMachine(STATE_GRIP)) {
    _servoGrip.write(90);
    _servoLift.write(10);  
    _eState = STATE_GRIP;
  }
}

void ServoAction::LiftGrip()
{
  if (StateMachine(STATE_LIFTGRIP)) {
    _servoGrip.write(90);
    _servoLift.write(30);
    delay(10);
    _eState = STATE_LIFTGRIP;
  }
}

bool ServoAction::StateMachine(ESTATE eNextState)
{
  switch (_eState) {
    case STATE_OPENGRIP:
      if (eNextState == STATE_LIFTGRIP) {
        return false;
      }
      break;
    case STATE_LIFTGRIP:
      if (eNextState == STATE_OPENGRIP) {
        return false;
      }
  }
  return true;
}



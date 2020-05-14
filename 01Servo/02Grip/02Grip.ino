#include <JellibiButton.h>

#include "ServoAction.h"

JellibiButton _btnUP;
JellibiButton _btnDown;
JellibiButton _btnRight;

ServoAction _servoAction;

void setup() {
  // put your setup code here, to run once:
  _btnUP.Init(A0, false);
  _btnDown.Init(A1, false);
  _btnRight.Init(4, false);
  _servoAction.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (_btnUP.Check())
  {
    _servoAction.LiftGrip();
  }
  if (_btnDown.Check())
  {
    _servoAction.Grip();      
  }
  if (_btnRight.Check())
  {
    _servoAction.OpenGrip();
  }
}

#include <JellibiPin.h>

#include <JellibiButton.h>

JellibiPin _pin;
JellibiButton _btnUP;
JellibiButton _btnDown;
JellibiButton _btnRight;
JellibiButton _btnLeft;

const int _speed = 100;
double _centerValue = 0;
bool _bRun = false;
bool _bDebug = false;

void MoveJellibi();
void StopJellibi();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  _btnUP.Init(_pin.Button(U), false);
  _btnDown.Init(_pin.Button(D), false);
  _btnRight.Init(_pin.Button(R), false);
  _btnLeft.Init(_pin.Button(L), false);
  pinMode(_pin.Ir(L), INPUT);
  pinMode(_pin.Ir(R), INPUT);  
  pinMode(_pin.WheelDir(L), OUTPUT);
  pinMode(_pin.WheelDir(R), OUTPUT);
  pinMode(_pin.Led(C), OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (_btnUP.Check() && !_bRun) {
    _bRun = true;
    _centerValue = analogRead(_pin.Ir(R)) - analogRead(_pin.Ir(L));
  }

  if (_btnDown.Check()&& _bRun) {
    _bRun = false;
  }
  
  if (_btnRight.Check() && _bRun) {
    _bRun = false;
  }
  
  if (_btnLeft.Check() && _bRun) {
    Serial.print("left\n");
    _bRun = false;
  }
  
  if (_bRun) {
    MoveJellibi(); 
  } else {
    StopJellibi();
  } 
}
void StopJellibi()
{
  analogWrite( _pin.Wheel(L), 0);
  analogWrite( _pin.Wheel(R), 0);
}
void MoveJellibi()
{
  double turnSpeed = ((analogRead(_pin.Ir(R))-analogRead(_pin.Ir(L))) - _centerValue )/4;
  double leftSpeed = _speed + turnSpeed;
  double rightSpeed = _speed - turnSpeed;

  if (leftSpeed > 0) {
    digitalWrite(_pin.WheelDir(L), 1);
  } else {
    digitalWrite(_pin.WheelDir(L), 0);
  }
  if (rightSpeed > 0 ) {
    digitalWrite(_pin.WheelDir(R), 0);
  } else {
    digitalWrite(_pin.WheelDir(R), 1);
  }
  analogWrite( _pin.Wheel(L), round(abs(leftSpeed)));
  analogWrite( _pin.Wheel(R), round(abs(rightSpeed)));
}

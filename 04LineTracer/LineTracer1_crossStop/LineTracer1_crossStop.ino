

#include <JellibiButton.h>
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

#define PIN_BUTTON_UP A0
#define PIN_BUTTON_DOWN A1
#define PIN_BUTTON_LEFT 2
#define PIN_BUTTON_RIGHT 4
#define PIN_IR_LEFT A6
#define PIN_IR_RIGHT A7
#define PIN_DIR_LEFT 7
#define PIN_DIR_RIGHT 8
#define PIN_PWM_LEFT 5
#define PIN_PWM_RIGHT 6
#define PIN_LED_RED 10

#define IR_TH 900

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  _btnUP.Init(PIN_BUTTON_UP, false);
  _btnDown.Init(PIN_BUTTON_DOWN, false);
  _btnRight.Init(PIN_BUTTON_RIGHT, false);
  _btnLeft.Init(PIN_BUTTON_LEFT, false);
  pinMode(PIN_IR_LEFT, INPUT);
  pinMode(PIN_IR_RIGHT, INPUT);  
  pinMode(PIN_DIR_LEFT, OUTPUT);
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_PWM_LEFT, OUTPUT);
  pinMode(PIN_PWM_RIGHT, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (_btnUP.Check() && !_bRun) {
    _bRun = true;
    _centerValue = analogRead(PIN_IR_RIGHT) - analogRead(PIN_IR_LEFT);
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
  analogWrite( PIN_PWM_LEFT, 0);
  analogWrite( PIN_PWM_RIGHT, 0);
}
void MoveJellibi()
{
  if(analogRead(PIN_IR_RIGHT)>IR_TH && analogRead(PIN_IR_LEFT)>IR_TH){
    _bRun = false;
    return;
  } //cross 만나면 멈춤.
  
  double turnSpeed = ((analogRead(PIN_IR_RIGHT)-analogRead(PIN_IR_LEFT)) - _centerValue )/6;
  double leftSpeed = _speed + turnSpeed;
  double rightSpeed = _speed - turnSpeed;

  if (leftSpeed > 0) {
    digitalWrite(PIN_DIR_LEFT, 0);
  } else {
    digitalWrite(PIN_DIR_LEFT, 1);
  }
  if (rightSpeed > 0 ) {
    digitalWrite(PIN_DIR_LEFT, 1);
  } else {
    digitalWrite(PIN_DIR_RIGHT, 0);
  }
  analogWrite( PIN_PWM_LEFT, round(abs(leftSpeed)));
  analogWrite( PIN_PWM_RIGHT, round(abs(rightSpeed)));
}

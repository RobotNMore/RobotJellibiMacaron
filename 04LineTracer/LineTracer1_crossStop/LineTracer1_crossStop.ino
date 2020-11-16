
//JellibiButton Library 추가
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

/**
 * Pin Number
 */
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

//IRSensor Threshold
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
  
  // 위 버튼을 눌러 라인트레이스를 시작한다.
  if (_btnUP.Check() && !_bRun) {
    _bRun = true;
    _centerValue = analogRead(PIN_IR_RIGHT) - analogRead(PIN_IR_LEFT);
  }
  
  // 다른 버튼을 누를경우 라인트레이스를 중지한다.
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
    MoveJellibi(); //LineTrace
  } else {
    StopJellibi(); //Stop
  } 
}
void StopJellibi()
{
  analogWrite( PIN_PWM_LEFT, 0);
  analogWrite( PIN_PWM_RIGHT, 0);
}
void MoveJellibi()
{
  /**
   * LineTrace 하기 전에 Cross를 만났는지 체크하여
   * 만났을 경우 LineTrace를 중지한다.
   */
  if(analogRead(PIN_IR_RIGHT)>IR_TH && analogRead(PIN_IR_LEFT)>IR_TH){
    _bRun = false;
    return;
  } 

  /**
   * LineTrace
   */
  // trunSpeed의 나누기 상수(6)를 조절하여 회전 각도를 조절할 수 있다.  
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

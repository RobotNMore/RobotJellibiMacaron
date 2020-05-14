#include <Servo.h>

#include <JellibiButton.h>

#define SERVO01_PIN 9
#define SERVO02_PIN 2

JellibiButton _up;
JellibiButton _down;

Servo _servo;
int _angle;
int _servoPin = SERVO01_PIN;

void Monitor() 
{
  if (Serial) 
  {
    Serial.print("Servo ");
    if (_servoPin == SERVO01_PIN){
      Serial.print(" 01 :");
    } else {
      Serial.print(" 02 :");
    }
    Serial.print(String(_angle)+"\n");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  _up.Init(A0, true);
  _down.Init(A1, true);

  _servo.attach(_servoPin);
  _angle = 45;
  _servo.write(_angle);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (_up.Check()) {
    _angle++;
    if (_angle > 180){
      _angle = 180;
    }
    _servo.write(_angle);
    Monitor();
  }
  
  if (_down.Check()) {
    _angle--;
    if (_angle < 0) {
      _angle = 0;
    }
    _servo.write(_angle);
    Monitor();
  }
}

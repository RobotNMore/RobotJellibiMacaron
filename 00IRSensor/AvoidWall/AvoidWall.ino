#define LeftWheelDir 7
#define RightWheelDir 8
#define LeftWheelPwm 5
#define RightWheelPwm 6
#define Threshold 880
double LEFT;
double CENTER;
double RIGHT;

void Forward(double RIGHT_VEL, double LEFT_VEL)
{
  digitalWrite(LeftWheelDir, 1);
  delay(50);
  analogWrite(LeftWheelPwm, LEFT_VEL);
  digitalWrite(RightWheelDir, 0);
  delay(50);
  analogWrite(RightWheelPwm, RIGHT_VEL);
}
void Backward(double RIGHT_VEL, double LEFT_VEL)
{
  digitalWrite(LeftWheelDir, 0);
  delay(50);
  analogWrite(LeftWheelPwm, LEFT_VEL);
  digitalWrite(RightWheelDir, 1);
  delay(50);
  analogWrite(RightWheelPwm, RIGHT_VEL);
}
void LeftBackward(double RIGHT_VEL, double LEFT_VEL) { //왼 - 뒤 오- 앞
  digitalWrite(LeftWheelDir, 0);
  delay(50);
  analogWrite(LeftWheelPwm, LEFT_VEL);
  digitalWrite(RightWheelDir, 0);
  delay(50);
  analogWrite(RightWheelPwm, RIGHT_VEL);
}
void RightBackward(double RIGHT_VEL, double LEFT_VEL) {
  digitalWrite(LeftWheelDir, 1);
  delay(50);
  analogWrite(LeftWheelPwm, LEFT_VEL);
  digitalWrite(RightWheelDir, 1);
  delay(50);
  analogWrite(RightWheelPwm, RIGHT_VEL);
}
void _loop() {
}
void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT); // button
  pinMode(LeftWheelDir, OUTPUT); // dirve
  pinMode(LeftWheelPwm, OUTPUT);
  pinMode(RightWheelDir, OUTPUT);
  pinMode(RightWheelPwm, OUTPUT);
  pinMode(A6, INPUT); // IR
  pinMode(A3, INPUT);
  pinMode(A7, INPUT);
  pinMode(10, OUTPUT); // LED
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  //오른쪽 버튼 누르면 동작
  while (!(digitalRead(4) == 0))
  {
    _loop();
  }
  Forward(80, 80);
}
void BlinkLED1(int pinNum) {
  digitalWrite(pinNum, HIGH);
  delay(1000);
  digitalWrite(pinNum, LOW);
}
void BlinkLED2(int pinNum) {
  digitalWrite(pinNum, HIGH);
  delay(300);
  digitalWrite(pinNum, LOW);
  delay(300);
  digitalWrite(pinNum, HIGH);
  delay(400);
  digitalWrite(pinNum, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  LEFT = analogRead(A7);
  CENTER = analogRead(A3);
  RIGHT = analogRead(A6);
  Forward(80, 80);
  if (RIGHT <= Threshold && LEFT > Threshold && CENTER > Threshold) { //IR센서 1개
    RightBackward(70, 20);
    BlinkLED1(10);
  }
  else if (LEFT <= Threshold && RIGHT > Threshold && CENTER > Threshold) {
    LeftBackward(20, 70);
    BlinkLED1(11);
  }
  else if (RIGHT <= Threshold && CENTER <= Threshold && LEFT > Threshold) { //IR센서 2개
    RightBackward(80, 40);
    BlinkLED2(10);
  }
  else if (LEFT <= Threshold && CENTER <= Threshold && RIGHT > Threshold) {
    LeftBackward(40, 80);
    BlinkLED2(11);
  }
  else if (RIGHT <= Threshold && CENTER <= Threshold && LEFT <= Threshold) { //IR센서 3개다 인식
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    Forward(0, 0);
    delay(50);
    Backward(80, 80);
    delay(1000);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    if (RIGHT < LEFT) {
      Forward(80, 40);
      BlinkLED1(11);
    }
    else if (LEFT < RIGHT) {
      Forward(40, 80);
      BlinkLED1(10);
    }
    else if (LEFT == RIGHT) { //랜덤 방향
      int rnd = random(0, 2);
      if (rnd == 0) {
        Forward(40, 80);
        BlinkLED1(11);
      }
      else {
        Forward(80, 40);
        BlinkLED1(10);
      }
    }

  }

}

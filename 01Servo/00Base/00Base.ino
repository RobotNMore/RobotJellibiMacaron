#include <Servo.h>

// 집게 구동 서보모터
int   pinNumberForServoMotor1 = 9;
Servo servoMotor1;

// 높낮이 구동 서보모터
int   pinNumberForServoMotor2 = 2;
Servo servoMotor2;

void setup() {
  // put your setup code here, to run once:
  servoMotor1.attach(pinNumberForServoMotor1);
  servoMotor2.attach(pinNumberForServoMotor2);

  // 기본 위치 설정 10 도로 제어  
  servoMotor1.write(10);
  servoMotor2.write(10);
  
  delay(20);  
}

void loop() {
  // put your main code here, to run repeatedly:

  // 0 ~ 90 도 까지 10도 간격으로 제어 
  for (int i = 10; i <= 90; i+=10)
  {
    servoMotor1.write(i);
    servoMotor2.write(i);
    delay(20);
  }
  delay(1000);
  // 90 도에서 10 도로 10도 간격으로 제어 
  for (int i = 90; i >= 10; i-=10)
  {
    servoMotor1.write(i);
    servoMotor2.write(i);
    delay(20);
  }
  delay(1000);
}

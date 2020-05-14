SonarLineTrace
----

라인트레이서 동작을 초음파 센서와 함께 할 수 있습니다.

초음파 센서를 사용하여 라인트레이스를 하면서 중간에 장애물을 보고 멈추도록 하였습니다.

***
이 코드의 LineTracer동작은 `04LineTrace` 코드와 기본적인 동작원리는 같지만 소스코드는 완전히 같지 않습니다.

크게 두가지 Class를 만들어 추가하였는데,`Drive Class`에서 라인트레이스를 하고 `SonarControl Class`에서 초음파 센서와 서보모터를 제어합니다.

- `loop()`
  - Drive Class에서 라인트레이스를 진행하며 주행합니다.
  - 계산된 angle값을 이용하여 서보를 움직여줍니다. 
  - 초음파 센서를 이용하여 7cm이내에 장애물이 있을 경우 0.6초간 멈춰줍니다.
    -  `
 if(_sonarCon.SonarRead() < 7){
   _drive.Stop();
   delay(600);
  } `

- `SonarControl Class`
  - `SonarRead()` 함수의 동작은 `SonarTest.ino`에 쓰인 코드와 완전히 같습니다.
  - `Init()` 함수에서 초음파 핀 뿐 아니라 서보모터 핀을 붙여주고, 서보 중간값으로 초기화 시켜줍니다.
  - `ServoWrite(int n)` 함수에서 서보를 n각도로 회전시켜줍니다.
- `Drive Class`
  - `LineTrace()` 함수에서 라인트레이서 동작을 진행합니다.  
    - 라인트레이스를 하면서 장애물도 탐지할 수 있도록 SonarClass의 `SonarRead()`함수를 사용하였습니다.
    - 바퀴 회전에 사용되는 turnSpeed 변수를 이용하여 서보모터의 각도도 조정할 수 있도록 *angle*을 계산하여 return하였습니다.
      - `int servoAngle = SERVO_MIDDLE_ANGLE - turnSpeed;`
  - 라인의 미끄러운 주행을 위해 미세한 값들(회전 반경, 속도 등)을 조절하였습니다.  
  
***

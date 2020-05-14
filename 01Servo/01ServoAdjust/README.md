# "ServoAdjust" 



### 그리퍼 Gripper  

그리퍼는 사람의 손가락을 흉내내어 사물을 쥐거나 놓을 수 있도록  만들어진 구조입니다.   
젤리비보드에 두 개의 서보모터를 적용하여 Gripper 로 동작할 수 있습니다.  

로봇젤리비에서 사용하는 서보모터는 동작 범위가 0도에서 180 도로써 그리퍼로 제어하는데 필요한 범위를 넘어섭니다. _**ServoAdjust**_ 샘플을 통해서 Gripper 로 알맞게 동작하기 위해, 두 개의 서보를 어느 정도 각도로  제어하여야 하는 지 알아 낼 수 있습니다. 

### Source Code 

**`Base`** 샘플에서 `Servo` 라이브러리를 사용하는 법을 익혔습니다.  이번에는 기본 라이브러리가 아닌 제3자(Third Party) 오픈 소스 라이브러리를 이용하여 손쉽게 구현하도록 합니다. 

##### 제3자(Third Party) 라이브러리 

젤리비보드에는 총 네개의 버튼이 있습니다. 이 버튼들을 이용하여 젤리비 그리퍼를 조작할 수 있습니다.  젤리비보드의 버튼들은 하나씩 젤리비보드의 핀(포트) 에 연결되어 있고 평소에는 HIGH(1) 였다가 사용자가 버튼을 누르면 LOW(0) 로 신호값이 변하게 됩니다.   

| 젤리비보드 핀(포트) |     기능 1     |  기능 2  |
| :-----------------: | :------------: | :------: |
|         A0          |  버튼 1 (UP)   |    -     |
|         A1          | 버튼 2 (DOWN)  |    -     |
|         D2          | 버튼 3 (LEFT)  | Servo 02 |
|         D4          | 버튼 4 (RIGHT) |    -     |

네개의 버튼을 편리하게 사용하기 위해 JellibiButton 라이브러리를 사용합니다.   


##### JellibiButton 라이브러리 포함하기 

젤리비버튼 라이브러리의 깃허브 저장소(http://github.com/signaled/JellibiButton) 의 설명대로 라이브러리를 다운로드 하여 적용합니다.

##### 소스코드 구조 

아두이노의 코드는 처음 한번 만 실행되는 `setup()` 함수와  계속해서 호출 되는 `loop()` 함수로 이루어져 있습니다.  
`Servo` 라이브러리와 `JellibiButton` 라이브러리 클래스의 인스턴스를 선언하여 오브젝트를 만들고 `setup()` 함수 안에서 인스턴스의 초기화를 합니다. 

``` c++
#include <Servo.h>  // 아두이노 서보 라이브러리 포함 
#include <JellibiButton.h> // 젤리비버튼 Third Party 라이브러리 포함 

#define SERVO01_PIN 9
#define SERVO02_PIN 2

Servo _servo;
JellibiButton _up;
JellibiButton _down;
int _angle = 45;   // Servo 모터의 제어 각도값을 할당
int _servoPin = SERVO01_PIN;  // Servo 01 포트인 9번을 할당 
void setup() {
    Serial.begin(115200);
    _up.Init(A0, true);       // A0 포트를 _up 인스턴스로 감시하도록 초기화 
    _down.Init(A1, true);     // A1 포트를 _down 인스턴스로 감시하도록 초기화
    _servo.attach(_servoPin); // _servoPin 에 할당된 Servo 01 포트를   
                              // Servo 에서 사용하도록 할당 
    _servo.write(_angle);	  // Servo 01 포트를 _angle 에 담겨있는 값으로 제어
}
```



`loop()` 함수에서는 버튼의 눌림을 감지하여 제어 각도를 가감하고 그 값을 서보에 적용합니다.  

``` c++
void loop() {
  if (_up.Check()) {
    _angle++;
    if (_angle > 180){
      _angle = 180;
    }
    _servo.write(_angle);
    Monitor();	// 현재 서보 제어 상태를 시리얼 포트로 전송 
  }
  
  if (_down.Check()) {
    _angle--;
    if (_angle < 0) {
      _angle = 0;
    }
    _servo.write(_angle);
    Monitor(); // 현재 서보 제어 상태를 시리얼 포트로 전송 
  }
}
```



### _**ServoAdjust.ino**_ 실행

1. 아두이노가 설치 된 PC 와 Gripper 를 연결한 젤리비보드를  USB 케이블로 연결하고 전원스위치를 켭니다.   
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다.  
2. 아두이노 툴을 PC 에서 실행시키고 젤리비보드와 연결된 포트를 메뉴(툴 > 포트)에서 선택합니다.  
   또, 메뉴(툴 > 보드) 에서 'Arduino Nano' 를 선택하고 프로세서 메뉴(툴> 프로세서) 도  'Atmega328P (old bootloader)' 를 선택합니다.
3. **ServoAdjust.ino** 파일을 아두이노 툴에서 열고 `컴파일(Ctrl+R)`합니다.
4. 컴파일에 문제가 없음이 확인 되면 `업로드(Ctrl+U)` 합니다.
5. 아두이노 툴의 `시리얼 모니터 (Ctrl+Shift+M)`  를 열고 창 하단의 보드레이트를 `115200` 으로 변경합니다. 
6. 상/하 버튼을 눌러 서보에 전달하는 각도를 조정하여 동작 범위를 확인 합니다.
7. 15번째 라인의 `_servoPin` 변수에 값을 `SERVO02_PIN` 으로 변경하여 4번부터 6번까지를 다시 실행합니다. 

 
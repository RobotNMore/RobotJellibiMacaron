# "DriveWithBluetooth"



### DriveWithBluetooth

로봇젤리비의 주행제어를 `HC-06 Bluetooth 모듈` 에서 명령을 받아 처리하게 되면 젤리비보드로 "RC 자동차" 를 구현할 수 있습니다. 

 `DriveWithBluetooth` 에서는 아래 명령어 목록대로 동작합니다.

|     명령어     |  기능  |
| :------------: | :----: |
| 'U' (또는 'u') |  전진  |
| 'D' (또는 'd') |  후진  |
| 'R' (또는 'r') | 우회전 |
| 'L' (또는 'l') | 좌회전 |
| 'S' (또는 's') |  정지  |



##### 전진과 후진 

로봇젤리비에서 전진과 후진은 좌/우 각 모터의 회전속도제어 핀(포트) 에 동일한 PWM 을 발진하고, 회전방향제어 핀(포트)에 반대의 값으로 제어 합니다. 

전진 시 회전방향 핀(포트) 의 제어는 아래 표와 같이 합니다. 

|      | D7 (왼쪽 주행모터 회전방향) | D8 (오른쪽 주행모터 회전방향) |
| :--: | :-------------------------: | :---------------------------: |
| 전진 |          HIGH (1)           |            LOW (0)            |
| 후진 |           LOW (0)           |            HIGH(1)            |



##### 회전 (좌회전과 우회전)

로봇젤리비에서 주행 중 각 모터의 회전속도제어 핀(포트)에 다른 PWM 값을 만들어 좌/우 측으로 회전합니다. 모터의 회전속도를 현재 속도보다 크게하여 반대편으로 회전하거나, 작게하여 제어하는 모터방향으로 회전할 수 있습니다.  이 두가지 회전구현의 회전반경에서 차이가 발생합니다.  `DriveWithBluetooth`에서는 회전하려는 방향측의 모터의 PWM 을 낮추어 회전하도록 구현 하였습니다.  

아래는 주행과 주행 중 회전 시 회전속도제어 핀(포트)의 PWM 수치를 입니다. 

|        | D5 (왼쪽 주행모터 회전속도) | D6 (오른쪽 주행모터 회전속도) |
| ------ | :-------------------------: | :---------------------------: |
| 주행   |             150             |              150              |
| 우회전 |             150             |              50               |
| 좌회전 |             50              |              150              |
| 멈춤   |              0              |               0               |

정지상태의 경우에 좌/우 주행모터의 회전방향을 반대로 하여 제자리에서 회전 하도록 합니다. 

|        | D7/ 왼쪽 주행모터 회전방향 | D8/ 오른쪽 주행모터 회전방향 |
| :----: | :------------------------: | :--------------------------: |
| 우회전 |          HIGH (1)          |           HIGH (1)           |
| 좌회전 |          LOW (0)           |           LOW (0)            |



### Source Code

`DriveWithBluetooth` 응용은 아래 그림과 같은 5개의 파일(README.md 는 제외) 로 이루어져 있습니다.

![Directory list in Grip](http://www.robotnmore.com/matthew/motor/drivewithbluetooth_dir.png)

`DriveWithBluetooth.ino` 에서는 `Drive` 클래스의 인스턴스를 생성고 `HC-06 Bluetooth 모듈` 에서 입력되는 명령에 맞춰 `Drive` 의 인스턴스 메소드를 호출합니다.  아래는 `DriveWithBluetooth.ino` 의 파일 내용입니다. 

``` cpp
#define RIGHT_PWM_PIN  6  
#define RIGHT_DIR_PIN  8

#define LEFT_PWM_PIN   5
#define LEFT_DIR_PIN   7

#define HC06_BAUDRATE 9600

#include "Drive.h"   // Drive 클래스 헤더 인클루드

Drive g_drive;		 // Drive 인스턴스 생성

void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06_BAUDRATE); // HC-06 Bluetooth 모듈 통신 설정
  g_drive.Init(RIGHT_PWM_PIN,  // Drive 인스턴스 초기화 
               RIGHT_DIR_PIN,  // 제어할 핀(포트) 설정
               LEFT_PWM_PIN, 
               LEFT_DIR_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    char cRead = Serial.read();
    Serial.write(cRead); // 스마트폰등의 블루투스 단말에 응답코드 전송
    
    switch(cRead) {
      case 'U':
      case 'u':
        g_drive.Go();
        break;
      case 'R':
      case 'r': 
        g_drive.Right();
        break;
      case 'D':
      case 'd':
        g_drive.Back();
        break;
      case 'L':
      case 'l':
        g_drive.Left();
        break;
      case 'S':
      case 's':
        g_drive.Stop();
        break;
      default:
        break;
    }
  }
}
```



#### "Wheel" Class

`Wheel` 클래스는 주행모터를 제어하기 위하여 만들어졌습니다. 초기화 메서드 (` void Init()` )에 모터제어 시 필요한 회전속도 제어용 PWM 파형 발진 핀(포트) 과 회전방향을 결정하는 GPIO 핀(포트) 의 번호를 전달받아 `pinMode()` 함수를 이용하여 각각 포트의 속성을 설정합니다. 

그리고 몇 개의 멤버메서드를 통해서 모터를 전/후진 및 회전하도록 제어할 수 있습니다.  

`Wheel` 클래스는 다음 설명할 `Drive` 클래스에서 좌/우 모터를 각각 담당하는 두개의 인스턴스로 사용됩니다.

아래는 `Wheel` 클래스의 멤버 메서드 입니다. 

---

``` c++ 
void Init(int pwmPin, int dirPin, bool bRightWheel);
```

###### Description : 

모터에 연결되는 PWM (회전속도 제어) 핀(포트)와 회전방향 핀(포트)의 번호를 인자로 받아 각 포트들을 초기화(`pinMode()` 설정) 합니다. 

###### Parameter :

> `int pwmPin` :  회전속도 제어 핀(포트) 번호  ( ex. 왼쪽모터의 경우 5 )  
> `int dirPin`  : 회전방향 제어 핀(포트) 번호  ( ex. 오른쪽모터의 경우 8 )  
> `bool bRightWheel` :    
>                          true : 오른쪽 모터    
>                          false : 왼쪽 모터   

---

``` c++
void Stop();
```

###### Description : 

모터의 PWM (회전속도 제어) 을 0 으로 하여 멈추게 합니다.

---

``` c++
void ForwardL();
```

###### Description :

회전방향 핀을 전진방향으로 제어하고 PWM (회전속도 제어) 을 50 으로 하여 저속 회전하도록 합니다. 이 함수는 좌/우 회전 시 사용됩니다. 

---

``` c++
void ForwardH();
```

###### Description : 

회전방향 핀을 전진방향으로 제어하고 PWM(회전속도 제어) 을 150 으로 하여 고속 회전하도록 합니다.  이 함수는 전/후진 시 사용됩니다.

---

``` c++
void BackwardL(); 
```

###### Description : 

회전방향 핀을 후진방향으로 제어하고 PWM(회전속도) 를 50 으로 하여 저속 회전하도록 합니다. 이 함수는 정지 시 좌/우 회전 시 사용됩니다.

---

``` cpp
void BackwardH();
```

###### Description : 

회전방향 핀을 후진방향으로 제어하고 PWM(회전속도) 를 150 으로 하여 고속 회전하도록 합니다. 이 함수는 후진 시 사용됩니다. 

---



#### "Drive" 클래스

`Drive` 클래스는 `Wheel` 클래스 인스턴스를 만들어 좌/우 두개의 모터를 명령에 따라 어떻게 동작시킬 지를 결정합니다. 

---

``` cpp
void Init(int rightPwmPin, int rightDirPin, int leftPwmPin, int leftDirPin);
```

###### Description : 

`Drive` 클래스의 멤버 인 두개의  `Wheel` 클래스 인스턴스를 인자로 넘겨 받은 좌/우 모터의 핀(포트) 정보로 초기화 합니다. 

###### Parameter :

> `int rightPwmPin` : 오른쪽 모터의 PWM 핀(포트)번호 (D6)   
> `int rightDirPin` : 오른쪽 모터의 회전방향제어 핀(포트) 번호 (D8)   
> `int leftPwmPin` : 왼쪽 모터의 PWM 핀(포트)번호 (D5)    
> `int leftDirPin` : 왼쪽 모터의 회전방향제어 핀(포트) 번호 (D7)

---

``` cpp
void Go();
```

###### Description : 

로봇젤리비를 전진 시킬 때 호출합니다.       
후진 상태인 경우에는 정지합니다. 

---

``` cpp
void Back();
```

###### Description : 

로봇젤리비를 후진 시킬 때 호출합니다.     
전진 상태인 경우 정지합니다. 

---

``` cpp
void Left();
```

###### Description : 

왼쪽 모터의 회전속도를 낮추어 좌회전합니다.  
정지 상태에서는 왼쪽 모터를 후진방향으로 회전시키고 오른쪽 모터를 전진방향으로 회전시켜 반시계 방향으로 회전합니다. 

---

``` cpp
void Right()
```

###### Description : 

오른쪽 모터의 회전속도를 낮추어 우회전합니다.     
정지 상태에서는 오른쪽 모터를 후진방향으로 회전시키고 왼쪽 모터를 전진방향으로 회전시켜 시계 방향으로 회전합니다. 

---



### _DriveWithBluetooth.ino_ 실행 

1. 아두이노가 설치 된 PC 와 젤리비보드를 USB 커넥터로 연결하고 전원스위치를 켭니다.  
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다. 
2. PC 에서 아두이노 툴을 실행하고 연결정보(보드, 포트, 프로세서) 를 설정합니다.
3. **DriveWithBluetooth.ino** 파일을 아두이노 툴에서 열고 `업로드(Ctrl+U)` 합니다.
4. `HC-06 블루투스 모듈` 을 젤리비보드의 `BT` 단자에 연결합니다. 
5. 스마트폰 등에서 블루투스를 켜고 `HC-06` 과 연결합니다. 
6. 'arduino bluetooth controller' 등의 앱에서 버튼등에 명령어 목록의 문자열을 맵핑한 후 버튼을 눌러 로봇젤리비를 조정합니다. 
# "GripperBluetoothDrive"



### GripperBluetoothDrive

로봇젤리비에 `HC-06 Bluetooth 모듈` 을 연결하여 스마트폰 앱을 통해 "RC 자동차" 뿐 아니라 Gripper 제어도 할 수 있습니다.  

서보모터 예제인 `Grip` 에서  사용한 `ServoAction` 클래스를 사용하여 손쉽게 구현할 수 있습니다. 

 `GripperBluetoothDrive` 에서는 아래 명령어 목록대로 동작합니다.

|     명령어     |    기능     |
| :------------: | :---------: |
| 'U' (또는 'u') |    전진     |
| 'D' (또는 'd') |    후진     |
| 'R' (또는 'r') |   우회전    |
| 'L' (또는 'l') |   좌회전    |
| 'S' (또는 's') |    정지     |
| 'O' (또는 'o') | 그리퍼 준비 |
| 'G' (또는 'g') | 그리퍼 닫음 |
| 'Q' (또는 'q') | 그리퍼 올림 |



### Source Code

`GripperBluetoothDrive` 응용은 아래 그림과 같은 7개의 파일(README.md 는 제외) 로 이루어져 있습니다.

![Directory list in Grip](http://www.robotnmore.com/matthew/motor/gripperdrive_dir.png)

기본 ino 파일외에 세개의 `c++` 클래스로 이루어져 있습니다.  이 클래스들의 인스턴스를 `GripperBluetoothDrive.ino` 파일에서 사용합니다. 

아래는 `GripperBluetoothDrive.ino` 의 파일 내용입니다. 

``` cpp
#define RIGHT_PWM_PIN  6  
#define RIGHT_DIR_PIN  8

#define LEFT_PWM_PIN   5
#define LEFT_DIR_PIN   7

#define HC06_BAUDRATE 9600

#include "ServoAction.h"	
#include "Drive.h" 			

ServoAction g_gripper;  // ServoAction 인스턴스 생성
Drive g_drive;		 	// Drive 인스턴스 생성

void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06_BAUDRATE); // HC-06 Bluetooth 모듈 통신 설정
  g_gripper.Init();			   // ServoAction 인스턴스 초기화
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
    
    switch(cRead)
    {
      case 'U':
      case 'u':
        g_drive.Go();	// 전진
        break;
      case 'R':
      case 'r': 
        g_drive.Right(); // 우회전
        break;
      case 'D':
      case 'd':
        g_drive.Back();  // 후진
        break;
      case 'L':
      case 'l':
        g_drive.Left();  // 좌회전
        break;
      case 'S':
      case 's':
        g_drive.Stop();  // 정지
        break;
      case 'O':
      case 'o':
        g_gripper.OpenGrip(); // 그리퍼 열기
        break;
      case 'G':
      case 'g':
        g_gripper.Grip();  // 그리퍼 쥐기
        break;
      case 'Q':
      case 'q':
        g_gripper.LiftGrip(); // 그리퍼 들어올리기 
        break;
      default:
        Serial.print("\nUnknown\n");
    }
  }
}
```





### _GripperBluetoothDrive.ino_ 실행 

1. 아두이노가 설치 된 PC 와 젤리비보드를 USB 커넥터로 연결하고 전원스위치를 켭니다.  
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다. 
2. PC 에서 아두이노 툴을 실행하고 연결정보(보드, 포트, 프로세서) 를 설정합니다.
3. **GripperBluetoothDrive.ino** 파일을 아두이노 툴에서 열고 `업로드(Ctrl+U)` 합니다.
4. `HC-06 블루투스 모듈` 을 젤리비보드의 `BT` 단자에 연결합니다. 
5. Gripper 와 연결된 서보모터도 포트에 연결합니다. 
6. 스마트폰 등에서 블루투스를 켜고 `HC-06` 과 연결합니다. 
7. 'arduino bluetooth controller' 등의 앱에서 버튼등에 명령어 목록의 문자열 맵핑한 후 버튼을 눌러 로봇젤리비를 조정합니다. 
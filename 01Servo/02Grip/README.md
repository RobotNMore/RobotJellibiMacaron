# "Grip"



### Grip 응용

`ServoAdjust` 예 에서 젤리비 Gripper 를 구성하는 두개의 서보모터를 제어하는 방법에 대해서 알 수 있었습니다. 

`Grip` 응용에서는 **"사물을 쥐고 들어올려 이동하고, 이동 후 바닥에 다시 내려 놓는다."** 는 시나리오를 구현하고 있습니다.  이를 위해서 아래의 세가지 동작을 정의하고 구현 합니다.

- 사물을 쥘 준비를 합니다.  (`OpenGrip` 상태)
- 사물을 쥡니다. (`Grip` 상태)
- 사물을 쥔 상태로 이동을 위해서  Gripper 를 살짝 들어 올립니다. (`LiftGrip` 상태)

우선 젤리비 Gripper 를 구성하는 두개의 서보모터를 아래와 같이 연결합니다. 

| 젤리비 포트 | 포트 명  | Servo 모터              |
| ----------- | -------- | ----------------------- |
| D9          | Servo 01 | 집게 제어 서보와 연결   |
| D2          | Servo 02 | 높낮이 제어 서보와 연결 |

### Source Code

`Grip` 응용은 아래 그림과 같은 세개의 파일(README.md 는 제외) 로 이루어져 있습니다.

![Directory list in Grip](http://www.robotnmore.com/matthew/servo/grip_dir.png)

`Grip.ino` 에서는 `ServoAction` 인스턴스를 생성고 버튼의 동작에 맞춰 인스턴스 메소드를 호출합니다.  아래는 `Grip.ino` 의 파일 내용입니다. 

``` c++
#include <JellibiButton.h> 
#include "ServoAction.h"  // 서보와 관련된 모든 동작을 ServoAction 클래스에서 구현
                          // 따라서 Grip.ino 에서는  
                          // 아두이노의 Servo 라이브러리를 포함하지 않는다.

JellibiButton _btnUP;
JellibiButton _btnDown;
JellibiButton _btnRight;

ServoAction _servoAction; // ServoAction 인스턴스 생성 

void setup() {
  // put your setup code here, to run once:
  _btnUP.Init(A0, false); 
  _btnDown.Init(A1, false);
  _btnRight.Init(4, false);
  _servoAction.Init();     
}

void loop() {
  // put your main code here, to run repeatedly:
  if (_btnUP.Check()) {      // UP 버튼을 눌렀을 때 
    _servoAction.LiftGrip(); // ServoAction 클래스의 LiftGrip() 메서드 호출
  }
  if (_btnDown.Check()) {    // Down 버튼을 눌렀을 때 
    _servoAction.Grip();     // ServoAction 의 Grip() 메서드 호출
  }
  if (_btnRight.Check()) {   // Right 버튼을 눌렀을 때 
    _servoAction.OpenGrip();  // ServoAction 의 OpenGrip() 메서드 호출 
  }
}
```



##### "ServoAction" Class

아두이노에서 라이브러리를 `c++` 로 구현할 수 있듯이 응용을 구현 할 때에도  `c++` 클래스를 구현하여 단정한 코드를 만들어 수 있습니다. 그 예로 `ServoAction` 클래스를 구현합니다. 

`ServoAction` 클래스는 `Grip` 응용에서의 시나리오를 구현하기 위한 서보모터 제어를 모두 구현하고 있습니다.    

아래는 `ServoAction` 클래스의 멤버 메서드 입니다. 

---

``` c++ 
void Init();
```

###### Description : 

서보포트(`Servo 01` 과 `Servo 02` 포트) 를 아두이노의 `Servo` 라이브러리와 연결하고 그리퍼를 초기 위치 (Grip() 메서드의 동작) 로 이동합니다.

---

``` c++
void Grip();
```

###### Description : 

집게를 제어하는 서보를 90도로 제어하여 쥐는 동작을 하고   
집게를 들어올리는 서보를 10도로 제어하여 살짝 들어 올려 바닥면과 접촉을 피합니다.

---

``` c++
void OpenGrip();
```

###### Description :

집게를 제어하는 서보를 0 도로 제어하여 여는 동작을 하고   
집게를 들어올리는 서보를 10도로 제어하여 살짝 들어 올려 바닥면과 접촉을 피합니다.

---

``` c++
void LiftGrip();
```

###### Description : 

집게를 제어하는 서보를 90도로 제어하여 쥐는 동작을 하고  
집게를 들어올리는 서보를 30도로 제어하여 들어올립니다. 

---

``` c++
void StateMachine(ESTATE eNextState); 
```

###### Description : 

`ServoAction` 클래스는 Gripper 로 사물을 쥐고 들어올려 이동하고   
이동 후 사물을 내려놓는 동작을 하도록 구성 하고 싶었습니다.    
`OpenGrip()` 상태에서 버튼을 잘못 눌러 `LiftGrip()` 메서드가 호출 되는 등의 원하지 않는 동작을  피하기 위하여 구현한 함수입니다.  이 함수는 `private` 속성을 가지고 있어 `Grip.ino` 에서는 호출 할 수 없습니다. 

---



### _Grip.ino_ 실행 

1. 아두이노가 설치 된 PC 와 젤리비보드를 USB 커넥터로 연결하고 전원스위치를 켭니다.  
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다. 
2. PC 에서 아두이노 툴을 실행하고 연결정보(보드, 포트, 프로세서) 를 설정합니다.
3. **Grip.ino** 파일을 아두이노 툴에서 열고 `업로드(Ctrl+U)` 합니다.
4. 젤리비 보드의 버튼(위/아래/오른쪽 세 개의 버튼) 을 눌러 Gripper 가 동작하는 것을 확인합니다. 
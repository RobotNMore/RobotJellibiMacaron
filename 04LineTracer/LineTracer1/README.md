# "LineTracer"



### LineTracer

 `Jellibi Mobile Board` 의 `IR Sensor`는 빛을 발광하고 반사되어 돌아오는 빛을 감지합니다.  밝은 바닥에 어두운 색의 라인을 만들어 (반대로 어두운 바닥면에 밝은 색의 라인을 만들어) `IR Sensor` 의 값의 변화됨에 따라 로봇젤리비의 주행모터를 제어하면 **"LineTracer"** 를 만들 수 있습니다.   

**"LineTracer"** 샘플에서는 밝은 색(빛의 반사가 원활합니다.)의 바닥면에 검은색 테이프(빛의 반사가 적어집니다.) 로 라인을 만들어 시작합니다.  `Jellibi Mobile Board` 의 센서선택 스위치를 `bottom` 쪽으로 옮겨 라인을 감지 할 수 있도록 준비합니다. 

**"LineTracer"** 동작을 시작할 때 두개 `IR Sensor` 에서 값을 읽어들여 기준값으로 합니다.   
주행을 시작하고 계속적으로 읽어 들이는 값을 아래처럼 처리합니다.   

1.  동작 시작 시 좌/우 `IR Sensor` 를 읽어 들여 기준값을 만듭니다.    
    **`기준값 = 오른쪽 IR 센서 값 - 왼쪽 IR 센서 값`** 
2. 주행 중 좌/우 IR Sensor 의 값을 읽어 들여 기준값과 같이 계산한 값을 만듭니다.   
   **`센서값 = 오른쪽 IR 센서 값 - 왼쪽 IR 센서 값`**
3. 센서값에서 기준값을 뺀 값은 로봇 젤리비를 오른쪽으로 회전하여야 하는지 왼쪽으로 회전하여야 하는지 또는  그대로 직진하여야 하는지를 알아 낼 수 있습니다. 이를 위해 판단값을 계산합니다.   
   **`판단값 = 센서값 - 기준값`**   
   _**"판단값 " 이 0 보다 크면**_   오른쪽 IR 센서의 값이 커졌거나 왼쪽 IR 센서의 값이 작아 졌다는 결론으로 "검은 테이프가 오른쪽 센서 가까워져 빛 반사가 줄어들었음 또는 왼쪽 센서가 검은 테이프와 멀어져 빛 반사가 많아 졌음" 으로 해석되며 그 결과로 _**오른쪽으로 회전하도록 제어**_ 합니다.   
   반대로 _**"센서값 - 기준값" 이  0보다 작으면**_ 왼쪽 IR 센서의 값이 커지거나 오른쪽 IR 센서의 값이 작아 졌다는 결론으로  "왼쪽 IR 센서가 검은 테이프에 가까워져 빛 반사가 줄어들었거나 오른쪽 IR 센사가 검은 테이프와 멀어져 빛 반사가 많아졌음" 으로 해석되므로 _**쪽으로 회전하도록 제어**_  합니다.   
4. **`판단값`** 의 크기를 회전반경을 결정하는데 사용됩니다.    
   예제에서는 판단값을 4로 나눈값을 좌/우 모터의 회전속도를 결정하는데 사용하고 있습니다. 

### Source Code

**"LineTracer"** 샘플에서는 **"JellibiPin"** 이라는 새로운 _Third Party Library_ 를 사용합니다.   
**"JellibiPin"** 라이브러리의 Github 저장소(https://github.com/signaled/JellibiPin) 에서 안내에 따라 라이브러리를 PC 에 다운로드하고 **Arduino Tool** 에 적용을 합니다.  **"JellibiPin"** 라이브러리는 버튼, IR 센서, 주행 모터, 부져, 조도센서 등이 젤리비보드의 어떠한 핀(포트)에 연결되어 있는지를 쉽게 코딩할 수 있도록 도와주는 라이브러리입니다. 

``` cpp 
#include <JellibiPin.h>

JellibiPin _pin
void loop() {
	double leftIRValue = analogRead(_pin.Ir(L)); // 왼쪽(L) Ir 센서의 값을 읽음
	double rightIRValue = analogRead(_pin.Ir(R));// 오른쪽(R) Ir 센서의 값을 읽음
	... 
}
```

  **"LineTracer"** 샘플에서는 두개의 버튼(`JellibiPin::Button()`)으로 시작과 종료를 하고, 동작 중 두개의 `IR Sensor` (`JellibiPin::Ir()`)에서 값을 읽어들여 두개의 모터의 회전방향(`JellibiPin::WheelDir()`)과 회전속도(`JellibiPin::Wheel()`)를 제어합니다.  **"JellibiPin"** 라이브러리를 사용하면 좀 더 가독성(Readability) 높은 코딩을 할 수 있습니다. 

### _LineTracer.ino_ 실행 

1. 아두이노가 설치 된 PC 와 젤리비보드를 USB 커넥터로 연결하고 전원스위치를 켭니다.  
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다. 
2. PC 에서 아두이노 툴을 실행하고 연결정보(보드, 포트, 프로세서) 를 설정합니다.
3. **LineTracer.ino** 파일을 아두이노 툴에서 열고 `업로드(Ctrl+U)` 합니다.
4. 책상이나 탁자에 검은색 테이프등을 붙여 주행경로를 만듭니다. 이 때 회전은 너무 급하지 않게 합니다. 
5. 시작점에 로봇젤리비를 위치시키고 `"UP"`버튼(A0) 를 눌러 시작합니다.   
6. 소스 코드에서 주행 속도등을 조정하여 라인을 따라가도록 튜닝합니다. 

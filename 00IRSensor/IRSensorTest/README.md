# "IRSensor" 



### IR 센서

젤리비보드에는 라인트레이서를 위한 **Mobile Board**에 두개의 IR 센서가 있으며  
주행 시 장애물 회피 용도의 **Sensor Board**에 세개의 IR 센서가 있습니다. 

IR 센서는 적외선을 발산하는 _**적외선 LED (IR Transmitter)**_ 와 적외선을 인식하는 _**포토트랜지스터 (IR Receiver)**_ 로 구성되어 있습니다.   적외선 LED 에서는 적외선을 발산하고 반사되어 오는 적외선을 `ADC(Analog Digital Converter)` 를 통해 감지 함으로써 장애물을 회피하거나 바닥의 라인을 따라갈 수 있게 됩니다.

IR 센서와 연결된 젤리비보드의 핀맵은 아래 표와 같습니다.

| 젤리비보드 핀 | Mobile Board 센서 | Sensor Board 센서 |
| :-----------: | :---------------: | :---------------: |
|      A3       |         -         |  가운데 IR 센서   |
|      A6       |   왼쪽 IR 센서    |   왼쪽 IR 센서    |
|      A7       |  오른쪽 IR 센서   |  오른쪽 IR 센서   |

젤리비 **Mobile Board** 에는 `FRONT` 와 `BOTTOM` 을 선택할 수 있는 스위치가 있습니다.   
이 스위치를  `FRONT` 로 옮기면 **Sensor Board** 와 연결되며 `BOTTOM` 으로 옮기게 되면 **Mobile Board** 와 연결되게 됩니다. 

### Source Code 

센서의 입력을 읽어 들이기 위해서 아두이노의 `analogRead` 함수를 사용합니다.   
`analogRead` 함수는 핀에 연결된 전압을 수치로 변환하는 함수로써 이러한 기능을 ADC (Analog to Digital Converter) 라고 합니다. 

`analogRead` 함수를 사용하여 **Mobile Board**의  IR 센서를 읽어 들이는 코드는 아래와 같습니다. (이 때 **Mobile Board** 의 스위치는 `BOTTOM` 으로 옮겨두어야 합니다. )

```c++
int valueLeft = analogRead(A6);
int valueRight = analogRead(A7);
```



### _**IRSensorTest.ino**_ 실행

1. 아두이노가 설치 된 PC 와 젤리비보드를  USB 케이블로 연결하고 전원스위치를 켭니다.   
   이 때 젤리비보드의 `PWR` LED 가 녹색으로 켜집니다. 
2. 아두이노 툴을 PC 에서 실행시키고 젤리비보드와 연결된 포트를 메뉴(툴 > 포트)에서 선택합니다.  또, 메뉴(툴 > 보드) 에서 'Arduino Nano' 를 선택하고 프로세서 메뉴(툴> 프로세서) 도  'Atmega328P (old bootloader)' 를 선택합니다.
3. **IRSensorTest.ino** 파일을 아두이노 툴에서 열고 `컴파일(Ctrl+R)`합니다.
4. 컴파일에 문제가 없음이 확인 되면 `업로드(Ctrl+U)` 합니다.
5. 아두이노 툴의 `시리얼 모니터 (Ctrl+Shift+M)`  를 열고 창 하단의 보드레이트를 `115200` 으로 변경합니다. 
6. 센서 앞을 손이나 사물등으로 가려 센서 값이 변경됨을 확인 합니다. 

 


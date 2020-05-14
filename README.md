# Quick Reference "Jellibi = Arduino Nano" 

<table id="Table_01" width="855" height="250" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td rowspan="3"><a href="http://www.robotnmore.com" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_01_1.jpg" width="221" height="180" alt=""></td>
	</a>
		<td>
			<a href="https://smartstore.naver.com/robotnmore" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_02_1.jpg" width="295" height="63" alt=""></td>
 			</a>		
		<td><a href="https://www.instagram.com/codecrunch.official/" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_03_1.jpg" width="339" height="63" alt=""></td>
			</a>
	</tr>
	<tr>
		<td><a href="https://blog.naver.com/robotnmore" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_04_2.jpg" width="295" height="58" alt=""></td>
			</a>
		<td><a href="https://www.facebook.com/codecrunch.official/" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_05_2.jpg" width="339" height="58" alt=""></td>
			</a>
	</tr>
	<tr>
		<td><a href="https://cafe.naver.com/codecrunch" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_06_1.jpg" width="295" height="59" alt=""></td>
			</a>
		<td><a href="https://www.youtube.com/channel/UCdlXy9DdpaUw1WaR7uf398Q" target="_blank">
			<img src="http://www.robotnmore.com/img/cafe_door_20191121_07_1.jpg" width="339" height="59" alt=""></td>
  			</a>	
</tr>
</table>


`RobotJellibiMacaron` 저장소(https://github.com/RobotNMore/RobotJellibiMacaron) 는 아두이노나노 호환보드인 젤리비보드를 이용하여 주행로봇, 그리퍼등을 구현하는 샘플코드가 있습니다.  

이 문서에서는 샘플코드를 이해하거나 사용하는 데 필요한 **아두이노 플랫폼**에 대한 간단한 설치 및 설정 방법을 소개합니다.  그리고 아두이노 플랫폼을 통해 **로봇젤리비를 움직이거나 그리퍼를 조작**하는데 필요한 기초적인 제어과 제어신호를 만들어 내는 방법에 대해 설명합니다. 

## 아두이노 설치 및 젤리비보드 연결

아두이노의 역사나 원리등의 배경지식은 [여기서(wikipedia)](https://ko.wikipedia.org/wiki/%EC%95%84%EB%91%90%EC%9D%B4%EB%85%B8) 살펴 볼 수 있습니다. 

- 아두이노 설치 
  - 윈도우즈의 마이크로소프트 스토어, 우분투의 소프트웨어 센터에서 아두이노를 설치 할 수 있습니다.
  - 또한 아두이노의 공식 홈페이지(https://www.arduino.com)에서도 아두이노 툴의 설치파일을 다운로드 받아 설치합니다.  
  
- 아두이노 실행 및 젤리비 보드 연결 
  - 아두이노와 젤리비보드의 연결은 시리얼포트를 통해 연결됩니다. 젤리비보드의 마이크로 USB 단자와 PC 의 USB 단자를 연결하면  윈도우는 젤리비보드와 연결할 수 있는 시리얼 포트를 만들어 준비합니다.    
    -  이 과정에서 "CH340" USB to Serial 칩셋  드라이버를 PC 에 설치 할 필요가 있습니다.  젤리비보드는 윈도우와 같은 OS 에서 시리얼 포트를 만들어 젤리비보드와 연결하도록 알려주는 "CH340" 칩셋을 가지고 있습니다. 
  - 윈도우의 장치 관리자에서 시리얼 포트의 이름(번호)를 확인하여 아두이노 툴에 적용합니다. 
    ex. COM1
  - 아두이노를 실행 한 후 **메뉴 > 툴 > 포트** 에 장치 관리자에서 확인한 시리얼포트를 선택합니다. 
    - **메뉴 > 툴 > 보드** 메뉴에 _**아두이노 나노(Arduino Nano)**_ 를 선택합니다. 
    - **메뉴 > 툴 > 프로세서** 메뉴에는 _**Atmega328P(Old bootloader)**_ 를 선택합니다.
  
- 기본 소스코드  

  - 아두이노는 처음 실행할 때 두개의 빈 함수를 준비해 줍니다. 

    ``` cpp 
    void setup() {
        
    }
    
    void loop() {
        
    }
    ```

  - `setup` 함수는 젤리비보드가 동작을 시작할 때 **처음에 한번** 호출 되는 함수입니다.   
    이 함수 안에는 동작을 준비하는 각종 초기화 코드를 적어 줍니다. 

  - `loop` 함수는 `setup` 함수가 호출 된 이후 계속해서 호출되어 동작하는 함수입니다.      
    이 함수 안에는 젤리비보드의 동작 내용을 코딩합니다.

- 젤리비보드에 코딩 적용 

  - `setup` 함수와 `loop` 함수를 모두 작성한 후 컴파일 및 다운로드하여 젤리비 보드를 움직일 수 있습니다. 

  - 아두이노 툴의 **메뉴 > 스케치 > 확인/컴파일** 메뉴를 선택하여 코드를 컴파일하고 젤리비보드에서 사용할 코드를 만듭니다. 이 때 코딩에 오류가 있을 경우 화면 하단에 오류내용을 표시하여 알려줍니다. 

  - 컴파일에 오류가 없으면 젤리비 보드에 코딩을 적용합니다. 아두이노 툴의 **메뉴 > 스케치 > 업로드** 를 선택하면 (컴파일하여) 업로딩을 진행합니다. 

  - 문제없이 업로드가 완료되면 곧 코드가 실행됩니다. 

    

## 아두이노에서 젤리비보드의 신호를 읽고 쓰기 

젤리비보드에 연결된 버튼의 입력을 받고 LED 를 켜고 서보를 움직이며 모터를 돌리기 위한 몇 가지 신호와 이 신호를 해석하는 방법에 대해 이해를 하면 코딩에 도움이 됩니다.   

젤리비보드에 가운데에는 정사각형 모양의 검은색 칩이 하나 있습니다. 이 칩 이름은 **"ATmega 328P"** 입니다. 우리가 아두이노 툴에서 작성한 코드를 컴파일하여 다운로드 하면 그 코드를 동작시키는 조그마한 프로세서(Micom) 입니다.  이 칩에 32개의 다리가 달려 있는데 이 다리를 ''핀(Pin)'' 이라고 칭합니다. 이 핀들에는 (직류)전원을 받도록 설계 된 핀도 있고, 접지(GND) 로 연결되는 핀도 있습니다. 또 버튼으로 연결되어 버튼의 상태를 알아 낼 수 있는 핀도 있으며 CDS (조도) 센서와 연결되어 주변 밝기를 알아낼 수 있는 핀도 있습니다. 

이런 핀들에 신호가 어떤식으로 들어오고 나가는지 또 신호를 해석하는 아두이노의 방법등을 소개합니다.

### GPIO (General Purpose Input/Output)

GPIO 는 가장 간단히 신호를 주고 받는 형태 입니다.  핀(포트) 과 연결된 선로의 상태를 LOW(0) 또는 HIGH(1) 두가지로 감지 또는 제어하는 방법입니다.

젤리비 보드에서 GPIO 는 버튼과 LED 를 제어하는데 사용됩니다.  또 모터의 회전방향을 제어하는데에도 사용됩니다. 

버튼의 눌림 여부에 따라 버튼과 핀(포트) 사이의 선로는 전기적으로 3.3V(HIGH, 1)  또는 0V(LOW, 0) 로 바뀌게 됩니다. 이 전기적인 변화를 `GPIO 입력` 으로 감지하여 버튼의 눌림 여부를 판단 합니다.

버튼과는 반대로 젤리비의 핀(포트)을 `GPIO 출력` 으로 제어하면 연결되어 있는 LED 를 켜거나 끌 수 있습니다.  

``` cpp 
void setup() {
    // 아두이노 에서는 핀을 GPIO 로 동작하도록 pinMode 함수로 초기화 합니다. 
    // pinMode 의 인자로 핀이름(번호) 와 제어 방향(입력/출력) 을 설정할 수 있습니다.
    pinMode(A1, INPUT); // 젤리비 보드의 버튼과 연결된 A1 핀을 GPIO 입력으로 설정합니다.
    pinMode(11, OUTPUT); //젤리비 보드에 LED 와 연결된 D11 핀을 GPIO 출력으로 설정합니다. 
}

void loop() {
    // 버튼을 누르면 A1 핀과 연결된 선로를 LOW 로 변경합니다. 
    // A1 핀(포트) 의 상태를 읽어들이는 함수로 아두이노에서는 digitalRead 를 사용합니다. 
    // digitalRead 함수의 인자로 핀이름(번호) 를 적어주고 
    // 응답으로 리턴값으로 HIGH(1) 또는 LOW(0) 를 받을 수 있습니다. 
    if (LOW == digitalRead(A1)) {
        // digitalWrite 함수를 사용하여 연결된 선로의 상태를 변경할 수 있습니다. 
        // 11번 핀의 상태를 HIGH(1) 로 변경함으로써 LED 를 켜게 됩니다.
        digitalWrite(11, HIGH);  
    } else {
        digitalWrite(11, LOW);
    }
}
```



### ADC (Analog Digital Converter)

ADC 는 핀(포트) 에 입력되는 전기적 신호가 얼마나 크고 작은지(전압이 얼마나 크고 작은지)를 수치화하는 방법을 제공합니다.  핀 이름이 A 로 시작하는 핀이 ADC 를 적용할 수 있는 핀(포트)입니다.  젤리비 보드에서 ADC 로 사용하는 핀은 CDS 센서(조도 센서)가 연결되어 있는 "A2" 포트, 센서 보드에 장착된 IR 센서와 연결된 "A3" / "A6" / "A7" 포트 등이 있습니다.  ADC 를 할 수 있는 능력이 있는 이러한 포트들을 아두이노에서는 아날로그포트 라고 부르며 이름의 첫번째에 'A' 를 붙여 부릅니다.

 CDS 센서(조도 센서, A2) 나 IR 센서 모두 빛을 감지하는 센서 입니다.  밝고 어두움의 **정도**를 ADC 를 이용하여 수치화 하고 프로그램에서 활용합니다. 

``` cpp 
void setup() {
    Serial.begin(115200);
	// 아두이노의 아날로그포트를 ADC 용도로 사용할 경우 
    // GPIO 초기화와 같이 pinMode 로 설정할 필요는 없습니다. 
}
void loop() {
    // A2 에 연결된 조도센서에서 밝기의 정도를 ADC 함
    // 아두이노에서 아날로그포트의 값을 ADC 할 때 analogRead 함수를 사용합니다.
    // 응답값의 범위는 0 ~ 1023 입니다. 최대값이 1023인 이유는  
    // 칩(Atmega328P) 의 구성에 따라 달라지게 됩니다. 
    int level = analogRead(A2);
    Serial.print("CDS Level :");
    Serial.println(level);
}
```

 

### PWM (Pulse Width Modulation)

PWM 은 주기를 가지는 파형을 이야기 합니다.  젤리비 보드에서는 이 PWM 파형을 만들어 모터(주행용 DC 모터, 그리퍼용 서보모터) 의 회전 속도 또는 회전 각도를 제어합니다. 또 LED 의 밝기도 제어할 수 있습니다. 

PWM 은 주기(Period) 와 듀티비(Duty ratio) 로 구성되는데, 주기는 한펄스가 만들어지는데 소요되는 시간이며 듀티비는 한펄스 에서 HIGH 인 구간이 얼마나 차지하는지(또는 LOW인 구간이 얼마나 되는지)를 나타내는데 이 두가지로 파형이 어떻게 생겼는지 판단할 수 있습니다. 

이 PWM 파형을 젤리비보드의 핀(포트)에서 만들어내고 모터를 제어하는 모터 드라이버 IC 에 전달합니다. 모터 드라이버 IC 는 PWM 파형을 읽어 듀티비(Duty Ratio) 을 알아내고 이를 모터의 회전속도를 제어하는 데 사용합니다. 

LED 와 연결된 핀(포트) 에서 PWM 을 만들어내고 듀티비에 조작하면 LED 의 밝기가 변화됩니다.   

젤리비보드에서는 주기는 제어하지 않고 듀티비만을 조작하여 모터를 제어합니다. 

``` cpp 
void setup() { 
    // 5, 6, 10, 11번 핀에서 PWM을 출력하기 위해   
    // 핀 속성을 OUTPUT 으로 설정합니다.
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
}
void loop() {
    // 5번핀 과 6번핀에 연결된 모터를 가감속합니다.
    // 10번핀과 11번핀에 연결된 LED의 밝기를 조정합니다.
    // 최대값은 255 이고 이때 듀티비는 100% 입니다.
    // 128 일 때에는 50%, 0일 때에는 0% 입니다.
    for (int i=0;i<255; i+=5){
        analogWrite(5, i);
        analogWrite(6, i);
        analogWrite(11, i);
        analogWrite(10, i);
        delay(50);
    }
    
    delay(100);
    // 5번핀과 6번핀에 연결된 모터를 감속함
    for (int i=255; i>=0; i-=5) {
        analogWrite(5, i);
        analogWrite(6, i);
        analogWrite(11, i);
        analogWrite(10, i);
        delay(50);
    }
    delay(100);
}
```



젤리비보드는 위에서 설명한 세가지 제어 신호 및 해석 방법으로 모든 동작을 완성할 수 있습니다. 

그리퍼를 사용하기 위해 서보모터를 제어할 경우 아두이노의 `Servo` 라는 이름의 라이브러리를 사용합니다. `Servo` 라이브러리를 사용하더라도 실제로 PWM 신호를 만들어내어 제어한다는 사실을 이해하고 있으면 코드를 작성하고 이해하는데 도움이 됩니다. 버튼을 사용할 때도 GPIO 입력을 통해서 버튼의 상태를 읽을 수 있다는 사실을 이해하며 코딩을 하면 젤리비를 통해 원하는 동작을 한층 쉽게 완성할 수 있습니다. 


#include <Servo.h> 

#define ENABLE_MOVE   1
#define ENABLE_LED    1

#define MOTOR_POWER_TEST  0

const int pinBuzzer = 3; // 부저핀 번호

const int pinBtnUp = A0; // 푸시버튼 핀 번호
const int pinBtnDown = A1;
const int pinBtnLeft = 2;
const int pinBtnRight = 4;

const int pinLedLeft =  10; // 왼쪽(빨강) LED
const int pinLedRight = 11; // 오른쪽(파랑) LED

////////////////////  라인트레이서 센서

// WHITE [290/230 .. 620/670 .. 910/900] BLACK
#define LT_MIDL_CNTR  540 // 512

#define LT_BLACK_TRU  (LT_MIDL_CNTR + 240)
#define LT_BLACK_AVG  (LT_MIDL_CNTR + 160)
#define LT_BLACK_MIN  (LT_MIDL_CNTR + 80)

#define LT_WHITE_MAX  (LT_MIDL_CNTR - 80)
#define LT_WHITE_AVG  (LT_MIDL_CNTR - 160)
#define LT_WHITE_TRU  (LT_MIDL_CNTR - 240)

const int pinLT1 = A6;  // IR 센서 1번(IN1) -- LEFT
const int pinLT2 = A7;  // IR 센서 2번(IN2) -- RIGHT

////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

const int pinDIR1 = 7; // 1번(왼쪽) 모터 방향 지정용 연결핀 번호
const int pinPWM1 = 5; // 1번(왼쪽) 모터 속도 지정용 연결핀 번호

const int pinDIR2 = 8; // 2번(오른쪽) 모터 방향 지정용 연결핀 번호
const int pinPWM2 = 6; // 2번(오른쪽) 모터 속도 지정용 연결핀 번호

const int motor1 = 1;  // 1번(왼쪽) 모터 번호
const int motor2 = 2;  // 2번(오른쪽) 모터 번호

const int turnCW = 0;  // 시계(CW) 방향 회전
const int turnCCW = 1; // 반시계(CCW) 방향 회전

////////////////////  좌우 모터 속력 조정

#define DRIVER_POWER    220
int Power = DRIVER_POWER; // 모터 회전 속력 = 정지 [0..255] 최대

float Power1Ratio = 0.96; // 1번(왼쪽), 최대 1.0 (보통 0.94 ~ 1.0 정도 보정)
float Power2Ratio = 1.00; // 2번(오른쪽), 최대 1.0

////////////////////  모터 회전 동작

#define MOTOR_L   0
#define MOTOR_R   1

#define FORWARD   0
#define BAKWARD   1

void move(int motor, int dir, int power)
{
  boolean dirHighLow;
  int     vp;

  if(motor == MOTOR_L)
  {
    if(dir == FORWARD)
      dirHighLow = HIGH;
    else // BAKWARD
      dirHighLow = LOW;
    
    vp = power * Power1Ratio;
    if( vp > 255 )
      vp = 255;
    else if( vp < 0 )
      vp = 0;
    
    digitalWrite(pinDIR1, dirHighLow);
    analogWrite(pinPWM1, vp);
  }
  else // MOTOR_R
  {
    if(dir == FORWARD)
      dirHighLow = LOW;
    else // BAKWARD
      dirHighLow = HIGH;
    
    vp = power * Power2Ratio;
    if( vp > 255 )
      vp = 255;
    else if( vp < 0 )
      vp = 0;
    
    digitalWrite(pinDIR2, dirHighLow);
    analogWrite(pinPWM2, vp);
  }
}

void  Forward( int power )  // 전진
{
  move(MOTOR_L, FORWARD, power);
  move(MOTOR_R, FORWARD, power);
}

void  Backward( int power )  // 후진
{
  move(MOTOR_L, BAKWARD, power);
  move(MOTOR_R, BAKWARD, power);
}

void  Left( int power )  // 좌회전
{
  move(MOTOR_L, BAKWARD, power);
  move(MOTOR_R, FORWARD, power);
}

void  Right( int power )  // 우회전
{
  move(MOTOR_L, FORWARD, power);
  move(MOTOR_R, BAKWARD, power);
}

void Stop()  // 정지
{
  analogWrite(pinPWM1, 0);
  analogWrite(pinPWM2, 0);
}

void  Forward2( int power1, int power2 )
{
  move(MOTOR_L, FORWARD, power1);
  move(MOTOR_R, FORWARD, power2);
}

void  BAKWARD2( int power1, int power2 )
{
  move(MOTOR_L, BAKWARD, power1);
  move(MOTOR_R, BAKWARD, power2);
}

////////////////////////////////////////////////////////////////////////////

void  setup()
{
  // 모터 제어 핀들을 모두 출력용 핀으로 설정
  
  pinMode( pinDIR1, OUTPUT ); // 1번(왼쪽) 모터 방향 핀을 출력 핀으로 설정
  pinMode( pinPWM1, OUTPUT ); // 1번(왼쪽)모터 속도 핀을 출력 핀으로 설정

  pinMode( pinDIR2, OUTPUT ); // 2번(오른쪽) 모터 방향 핀을 출력 핀으로 설정
  pinMode( pinPWM2, OUTPUT ); // 2번(오른쪽) 모터 속도 핀을 출력 핀으로 설정

  pinMode( pinLT1, INPUT ); // 바닥 완쪽 라인트레이스 센서
  pinMode( pinLT2, INPUT ); // 바닥 오른쪽 라인트레이스 센서

  pinMode( pinLedLeft, OUTPUT );  // 왼쪽(빨강) LED
  pinMode( pinLedRight, OUTPUT ); // 오른쪽(파랑) LED

  pinMode(pinBuzzer, OUTPUT); // 부저 핀을 출력 핀으로 설정

  pinMode(pinBtnUp, INPUT);  // 푸시버튼 핀을 입력용 핀으로 설정
  pinMode(pinBtnDown, INPUT);
  pinMode(pinBtnLeft, INPUT);
  pinMode(pinBtnRight, INPUT);

  Serial.begin( 38400 );  // 통신 초기화 (bps)

  // 장치 테스트 및 초기 상태 설정

  digitalWrite( pinLedLeft, LOW );
  digitalWrite( pinLedRight, LOW );

  noTone( pinBuzzer );  // 스피커 끄기 (OFF)
  Stop();  // 처음에는 정지 상태

#if ENABLE_MOVE
 #if MOTOR_POWER_TEST // 좌우 모터 회전속도 보정을 위한 테스트
  while( 1 )
  {    
    while( digitalRead(pinBtnLeft) != 0 )  // 버튼 눌림상태가 아니면
      delay( 10 );
    delay( 200 );
 
    Forward( Power );
    delay( 2000 ); 
    Stop();
    delay( 1000 );
  
    Backward( Power );
    delay( 2000 );
    Stop();
    delay( 1000 );
    
    Left( Power );
    delay( 1000 );
    Stop();
    delay( 1000 );
  
    Right( Power );
    delay( 1000 );
    Stop();
    delay( 3000 );
  }
 #endif
#endif
}

////////////////////////////////////////////////////////////////////////////

#if 0 //////////////////  Normal Speed

  #define MaxSpeed    220 // 최대 제한 속력(power= [0..255])
  #define BaseSpeed   170 // 직진 시 속력
  #define TURN_SPEED  150 // 좌우 회전 시 속도
  
  #define Kp   1.0
  #define Kd  90.0

  float DeltaspeedRightatio = 2.0;  // 감지된 바퀴쪽 센서 변화량의 모터파워 적용 비율

#else //////////////////  Top Speed

  #define MaxSpeed    255
  #define BaseSpeed   255
  #define TURN_SPEED  230
  
  #define Kp   0.8
  #define Kd  80.0
  
  float DeltaspeedRightatio = 2.7;

#endif

////////////////////////////////////////////////////////////////////////////

#define MAX_SENSOR_NOISE  10  // 노이즈로 간주하여 무시할 +/- 센서 변화값

int SensorWhiteLeft = 260;  // 기본 흰색 바닥 센서값
int SensorWhiteRight = 260;  // 기본 흰색 바닥 센서값


int GetSensorDeltaError( int v1, int v2 )
{
  int error1, error2;
  
  if( v1 > SensorWhiteLeft )  // 왼쪽 센서사 검은쪽 라인으로 치우침
    error1 = v1 - SensorWhiteLeft;
  else
    error1 = 0;
  
  if( v2 > SensorWhiteRight )  // 오른쪽 센서사 검은쪽 라인으로 치우침
    error2 = v2 - SensorWhiteRight;
  else
    error2 = 0;

  return  error1 - error2;
}


int RunState = 0; // 버튼 눌러서 주행/정지, 0=정지, 1=주행
int LastError = 2;  // 처음 버튼 누를 때 출발되도록



void  loop()
{

  if( digitalRead(pinBtnLeft) == 0 )  // 버튼 눌림 상태이면
  {      
    if( RunState )
    {
      Stop();
      RunState = 0;
    } else {
      SensorWhiteLeft = analogRead( pinLT1 ) + MAX_SENSOR_NOISE;
      SensorWhiteRight = analogRead( pinLT2 ) + MAX_SENSOR_NOISE;
      RunState = 1;
    }
    
    while( digitalRead(pinBtnLeft) == 0 )  // 버튼이 올려질 때 까지 대기
      delay( 10 );
    delay( 50 );
  }

  if( RunState == 0 )
  {
    delay( 10 );
    return;
  }
  
  int  v1 = analogRead( pinLT1 );
  int  v2 = analogRead( pinLT2 );

  if( (v1 > LT_BLACK_AVG) && (v2 < LT_WHITE_MAX) )  // 왼쪽만 검정, 완전 좌회전
  {
#if ENABLE_LED
    digitalWrite( pinLedLeft, HIGH );
    digitalWrite( pinLedRight, LOW );
#endif
    
#if ENABLE_MOVE
    move(MOTOR_L, BAKWARD, TURN_SPEED);
    move(MOTOR_R, FORWARD, TURN_SPEED);
#endif

    return;
  }
  
  if( (v1 < LT_WHITE_MAX) && (v2 > LT_BLACK_AVG) )  // 오른쪽만 검정, 완전 우회전
  {
#if ENABLE_LED
    digitalWrite( pinLedLeft, LOW );
    digitalWrite( pinLedRight, HIGH );
#endif    
 
#if ENABLE_MOVE
    move(MOTOR_L, FORWARD, TURN_SPEED);
    move(MOTOR_R, BAKWARD, TURN_SPEED);
#endif

    return;
  }
  
  if( (v1 > LT_BLACK_AVG) && (v2 > LT_BLACK_AVG) ) // 모두 검은색
  {
#if ENABLE_LED
    digitalWrite( pinLedLeft, HIGH );
    digitalWrite( pinLedRight, HIGH );
#endif    
    
#if ENABLE_MOVE
    move(MOTOR_L, FORWARD, TURN_SPEED);
    move(MOTOR_R, FORWARD, TURN_SPEED);
#endif

    return;
  }
  
  ////////// 모두 흰색(직진)이거나 기타 경우(센서값이 변화될 때)
  
#if ENABLE_LED
  digitalWrite( pinLedLeft, LOW );
  digitalWrite( pinLedRight, LOW );
#endif    

  int error = GetSensorDeltaError( v1, v2 );

  if( error != LastError )  // 센서 변화량이 다를때만 속도를 바꾸자...
  {
    int deltaSpeed = Kp * error + Kd * (error - LastError);
  
    LastError = error;
    
    if( deltaSpeed == 0 )  // 노이즈에 의한 미세한 변화량은 무시
      return;

    int speedLeft, speedRight;
    
    if( deltaSpeed > 0 ) // Left Turn
    {
      speedLeft = BaseSpeed - deltaSpeed * DeltaspeedRightatio;
      speedRight = BaseSpeed;
    }
    else  // Right Turn
    {
      speedLeft = BaseSpeed;
      speedRight = BaseSpeed + deltaSpeed * DeltaspeedRightatio;
    }

    // 속도가 0 이하 또는 255 이상 처리
    
    if (speedLeft < 0)
      speedLeft = 0;
    else if (speedLeft > MaxSpeed )
      speedLeft = MaxSpeed;
      
    if (speedRight < 0)
      speedRight = 0;    
    else if (speedRight > MaxSpeed )
      speedRight = MaxSpeed;
      
#if ENABLE_MOVE
    move(MOTOR_L, FORWARD, speedLeft);
    move(MOTOR_R, FORWARD, speedRight);
#endif

  }
  
}


/* DriveWithBluetooth.ino
 * 블루투스 채널로 입력되는 명령을 해석하여 모터구동 
 * U/u : 전진
 * D/d : 후진
 * R/r : 우회전
 * L/l : 좌회전
 */

#define RIGHT_PWM_PIN  6  
#define RIGHT_DIR_PIN  8

#define LEFT_PWM_PIN   5
#define LEFT_DIR_PIN   7

#define HC06_BAUDRATE 9600

#include "Drive.h"


Drive g_drive;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06_BAUDRATE);
  g_drive.Init(RIGHT_PWM_PIN, 
  			   RIGHT_DIR_PIN, 
  			   LEFT_PWM_PIN, 
  			   LEFT_DIR_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    char cRead = Serial.read();
    Serial.write(cRead);
    
    switch(cRead)
    {
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
        Serial.print("\nUnknown\n");
    }
  }
  

}

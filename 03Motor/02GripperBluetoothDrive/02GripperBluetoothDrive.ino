#include "ServoAction.h"
#include "Drive.h"

#define RIGHT_PWM_PIN  6  
#define RIGHT_DIR_PIN  8

#define LEFT_PWM_PIN   5
#define LEFT_DIR_PIN   7

#define HC06_BAUDRATE 9600

ServoAction g_gripper;
Drive g_drive;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06_BAUDRATE);
  g_gripper.Init();
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
      case 'O':
      case 'o':
        g_gripper.OpenGrip();
        break;
      case 'G':
      case 'g':
        g_gripper.Grip();
        break;
      case 'Q':
      case 'q':
        g_gripper.LiftGrip();
        break;
      default:
        Serial.print("\nUnknown\n");
    }
  }
}

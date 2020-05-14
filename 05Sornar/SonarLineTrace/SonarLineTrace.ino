
#include <Arduino.h>
#include "Drive.h"
#include "Define.h"
Drive _drive;

#include "SonarControl.h"
SonarControl _sonarCon;



void setup() {
  // put your setup code here, to run once:
  
  _drive.Init();
  _drive.InitSensor();
  _sonarCon.Init();

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  _drive.Sensing();
  int angle = _drive.LineTrace();
 // _sonarCon.ServoWrite(angle);
    
  if(_sonarCon.SonarRead() < 7){
   _drive.Stop();
   delay(600);
  }
}

#define HC06_BAUDRATE 9600
/*
 * HC06 블루투스 동글 설정 
 *  기본 통신(UART) 설정 : 9600 8N1
 *  기본 name : HC06
 *  기본 PIN  : 1234
 *  NAME 설정 명령 : AT+NAMEabcd "abcd" 로 이름 변경 
 *  PIN 설정 명령  : AT+PIN1234  "1234" 로 핀 변경 
 *   
 * 아두이노툴에서 펌웨어 다운로드 시에 HC06 탈거필요 
 * 
 * 스마트폰/태블릿과 패어링 
 *  1. 젤리비 보드에 펌웨어 다운로드 후 HC06 동글 장착
 *  2. 스마트폰에서 Bluetooth 활성화 후 주변장치 검색 
 *  3. HC06 과 패어링 진행 
 *  4. 앱스토어/앱마켓 등에서 "Arduino Bluetooth Controller" 등의 블루투스통신용 앱 설치  
 *  5. 블루투스 통신 앱 실행 후 접속 및 명령 전송 
 *  
 */
void CmdParse(char cmd)
{
  switch(cmd)
  {
    case 'U':
    case 'u':
      Serial.print("\nCmd[u/U]\n"); 
      break;
    case 'R':
    case 'r': 
      Serial.print("\nCmd[R/r]\n");
      break;
    case 'D':
    case 'd':
      Serial.print("\nCmd[D/d]\n");
      break;
    case 'L':
    case 'l':
      Serial.print("\nCmd[L/l]\n");
      break;
    case 'S':
    case 's':
      Serial.print("\nCmd[S/s]\n");
      break;
    case 'B':
    case 'b':
      Serial.print("\nCmd[B/b]\n");
      break;
    default:
      Serial.print("\nUnknown\n");
  }
};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06_BAUDRATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    char cRead = Serial.read();
    Serial.write(cRead);
    CmdParse(cRead);
  }
}

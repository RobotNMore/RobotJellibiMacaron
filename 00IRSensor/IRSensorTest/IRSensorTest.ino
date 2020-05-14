#define LEFT_IR_PIN   A6
#define CENTER_IR_PIN A3
#define RIGHT_IR_PIN  A7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int right = analogRead(RIGHT_IR_PIN);
  int left = analogRead(LEFT_IR_PIN);
  int center = analogRead(CENTER_IR_PIN);
  //Serial.print(String(left) + "/"+String(center)+"/"+String(right)+"\n");
  Serial.print(String(left) + "/"+String(right)+"\n");
  delay(50);
}

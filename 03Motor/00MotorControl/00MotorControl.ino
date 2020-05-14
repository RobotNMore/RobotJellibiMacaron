#define RIGHT_PWM_PIN  6  
#define RIGHT_DIR_PIN  8

#define LEFT_PWM_PIN   5
#define LEFT_DIR_PIN   7

#define MAX_PWM 255
#define HIGH_PWM 120
#define LOW_PWM  60
#define MIN_PWM 0

void lowSpeed(){
  analogWrite(RIGHT_PWM_PIN, LOW_PWM);
  analogWrite(LEFT_PWM_PIN, LOW_PWM);
}

void highSpeed(){
  analogWrite(RIGHT_PWM_PIN, HIGH_PWM);
  analogWrite(LEFT_PWM_PIN, HIGH_PWM);
}

void turnRight()
{
  digitalWrite(RIGHT_DIR_PIN, HIGH);
  digitalWrite(LEFT_DIR_PIN, HIGH);
}

void turnLeft()
{
  digitalWrite(RIGHT_DIR_PIN, LOW);
  digitalWrite(LEFT_DIR_PIN, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(LEFT_PWM_PIN, OUTPUT);
  pinMode(LEFT_DIR_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  highSpeed();
  turnRight();
  delay(3000);
  lowSpeed();
  turnLeft();
  delay(3000);
}

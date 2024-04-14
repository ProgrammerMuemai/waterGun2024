#include <Servo.h>
Servo myservo;

#define CH1 4
#define CH2 5
#define CH5 6
#define IN1_MOTOR 7
#define IN2_MOTOR 8
#define IN3_SHOOT 9
//#define IN4_REFILL 11

int ch1Value;
int ch2Value;
int ch5Value;


int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  pinMode(IN1_MOTOR, OUTPUT);
  pinMode(IN2_MOTOR, OUTPUT);
  pinMode(IN3_SHOOT, OUTPUT);
  pinMode(IN4_REFILL, OUTPUT);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  digitalWrite(IN1_MOTOR, HIGH);
  digitalWrite(IN2_MOTOR, HIGH);
}

void loop() {
  ch1Value = readChannel(CH1, -255, 255, 0);
  ch2Value = readChannel(CH2, -255, 255, 0);
  ch5Value = readChannel(CH5, -255, 255, 0);

  upDownControl(ch5Value);

 // Serial.println(ch1Value);

  if (ch2Value > 100) {
    digitalWrite(IN3_SHOOT, LOW);
    // Serial.println("SHOOT");
  } else {
    digitalWrite(IN3_SHOOT, HIGH);
     //Serial.println("STOP SHOOT");
  }

  /*if (ch2Value < -100) {
    digitalWrite(IN4_REFILL, LOW);
  } else {
    digitalWrite(IN4_REFILL, HIGH);
  }*/

  if (ch1Value < -150) {
    TurnLeft();
    Serial.println("TurnLeft");
  } else if (ch1Value > 150) {
    Serial.println("TurnRight");
    TurnRight();
  } else {
    digitalWrite(IN1_MOTOR, HIGH);
    digitalWrite(IN2_MOTOR, HIGH);
  }
}

void upDownControl(int val) {
  val = map(val, -265, 255, 0, 180);
  myservo.write(val);
 // Serial.println(String("myservo = ")+val);
}
void TurnRight() {
  digitalWrite(IN1_MOTOR, LOW);
  digitalWrite(IN2_MOTOR, HIGH);
}
void TurnLeft() {
  digitalWrite(IN1_MOTOR, HIGH);
  digitalWrite(IN2_MOTOR, LOW);
}

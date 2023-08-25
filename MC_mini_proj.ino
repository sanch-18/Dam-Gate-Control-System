#include <ESP32Servo.h>

const int buzzer = 5;
const int triggerPin = 2;
const int echoPin = 4;
int safe_lim = 100;
int danger_limit1 = 75;
int danger_limit2 = 50;
int danger_limit3 = 25;
int flag = 2;
long duration, distance;

Servo myservo;

void setup() 
{
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(18); // attach servo to pin 18
}

void loop() 
{
  digitalWrite(buzzer, LOW);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;

  if(distance>safe_lim)
  {
    myservo.write(0);
  }
  else if(distance<safe_lim && distance>danger_limit1)
  {
    myservo.write(30);
  }
  else if(distance<danger_limit1 && distance>danger_limit2)
  {
    myservo.write(60);
  }
  else if(distance<danger_limit2 && distance>danger_limit3)
  {
    myservo.write(90);
  }
  else
  {
    myservo.write(120);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm \n");
  delay(2000);
  digitalWrite(buzzer, LOW);

}

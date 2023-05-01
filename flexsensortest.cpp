
#include <Servo.h>

//declare flex sensors
const int flexPin_1 = A0;
const int flexPin_2 = A1;

//declare servos
const int servoPin_1 = 13;
const int servoPin_2 = 12;

//declare flex values
int flexValue_1;
int flexValue_2;

//declare servos
Servo servo1;
Servo servo2;

void setup()
{
  //initalize servo pos
  Serial.begin(9600);
  
  pinMode(flexPin_1, INPUT);
  pinMode(flexPin_2, INPUT);
  
  servo1.attach(servoPin_1);
  servo2.attach(servoPin_2);
}


void loop()
{
  //Range (767 - 964)
  flexValue_1 = analogRead(flexPin_1);
  flexValue_2 = analogRead(flexPin_2);
  
  //these values will change depending on servo.
  flexValue_1 = map(flexValue_1,767,964,0,90);
  flexValue_2 = map(flexValue_2,767,964,0,90);
  
  servo1.write(flexValue_1);
  servo2.write(flexValue_2);
  
}

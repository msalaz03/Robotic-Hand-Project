#include <Servo.h>

Servo servo1;
const int flexPin = A1; // pin A1 to read analog input

// Variables:
int value;
int flex1, flex2, flex3, flex4, flex5;  // use an array in the future
int sender_values[5];

void setup()
{
  servo1.attach(3);
  Serial.begin(9600); // initialize serial moniter read in and out at specified baud rate
}

void loop()
{
  value = analogRead(flexPin);

  flex1 = map(value, 750, 880, 0, 130); // INDEX
  flex1 = constrain(flex1, 0, 180); 

  // flex2 = map(value, 832, 935, 0, 103); // MIDDLE
  // flex2 = constrain(flex2, 0, 180);

  // flex3 = map(value, 741, 870, 0, 129); // THUMB
  // flex3 = constrain(flex3, 0, 180);

  // flex4 = map(value, 745, 858, 0, 113); // PINKY
  // flex4 = constrain(flex4, 0, 180);

  //Serial.println(flex1);
  servo1.write(flex1);
  
  //Serial.println(value);
 
  delay(500);
}
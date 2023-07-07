#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int flexPin = A1;
const int flexPin2 = A2;
const int ARRAY_SIZE = 2;
int flex1,flex2;


int msg[2];

void setup() {
  Serial.begin(9600);
  Serial.println("test");
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop() {

  flex1 = analogRead(flexPin);
  flex1 = map(flex1, 741, 870, 0, 129); // THUMB
  flex1 = constrain(flex1, 0, 180);

  flex2 = analogRead(flexPin2);
  flex2 = map(flex2, 832, 935, 0, 103); // MIDDLE
  flex2 = constrain(flex2, 0, 180);

  msg[0] = flex1;
  msg[1] = flex2;
  // flex1 = map(flex1, 750, 880, 0, 130); // INDEX
  // flex1 = constrain(flex1, 0, 180); 


  //sendString = atoi(flex1);


  // radio.write(&flex1, sizeof(flex1));
  radio.write(&msg, sizeof(msg));
  //radio.write(&sendString[1], strlen(sendString[1]) + 1);

  Serial.println("THUMB: " + String(msg[0]));
  Serial.println("MIDDLE: " + String(msg[1]));
  delay(500);
  
}
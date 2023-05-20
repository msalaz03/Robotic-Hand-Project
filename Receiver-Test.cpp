//Receiver Code
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReading(0, address);
  radio.setPALevel(RF_24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()){
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println(text);
  }

}

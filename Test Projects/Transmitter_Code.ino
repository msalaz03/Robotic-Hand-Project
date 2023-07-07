#include <SPI.h>                      //the communication interface with the modem
#include <nRF24L01.h>   
#include <RF24.h>

RF24 radio(7, 8);  // Create an instance of the RF24 class
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();  // Initialize the radio module
  radio.openWritingPipe(address);  // Set the address to which the data will be sent
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text [] = "Hello World";
  radio.write(&text, sizeof(text));  //Send the message
  delay(1000);  // Wait for a second before sending the next message
}
#include <SPI.h>                      //the communication interface with the modem
#include <nRF24L01.h>
#include <RF24.h>   

RF24 radio(7, 8);  // Create an instance of the RF24 class
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();  // Initialize the radio module
  radio.openReadingPipe(0, address);  // Set the address from which the data will be received
  radio.startListening();  // Put the radio module in listening mode
}

void loop() {

  if (radio.available()) {
    char text[32] = "";  // Buffer to store the received message
    radio.read(&text, sizeof(text));  // Read the message from the radio
    Serial.println(text);
  }
}



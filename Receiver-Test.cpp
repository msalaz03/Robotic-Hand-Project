//Receiver Code

#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const uint64_t address = 0xABCDABCDABCDLL; // Address between the transmitter and receiver

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Received message: ");
    Serial.println(text);
  }
}

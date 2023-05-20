#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const uint64_t address = 0xABCDABCDABCDLL; // Address between the transmitter and receiver

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  Serial.println("Message sent: Hello World");
  delay(1000);
}

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>


// Initialize Radio Data
RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

int transmit[5];

// Initialize Flex Sensor Data
const int flexPin1 = A1;
const int flexPin2 = A2;
const int flexPin3 = A3;
const int flexPin4 = A4;
const int flexPin5 = A5;

int value1, value2, value3, value4, value5;
int flex1, flex2, flex3, flex4, flex5;


// Initialize Button Data
const int buttonPin = 9;  // Pin connected to the push button
// const int ledPin = 13;    // Pin connected to the LED

int buttonState;
int lastButtonState = LOW;
int modeSelect = 1;  // Current mode: 0 for mode 1, 1 for mode 2

bool debounceActive = false;       // Flag to track if button debouncing is active
bool initialButtonChange = false;  // Flag to track the initial button state change

unsigned long lastModeChange = 0;   // Timestamp of the last mode change
unsigned long debounceDelay = 100;  // Debounce delay in milliseconds


void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(buttonPin, INPUT);
  Serial.println("Start Test");
}


void loop() {
  int buttonState = digitalRead(buttonPin);  // Read the current state of the button

  if (!initialButtonChange) {
    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == HIGH) {
        initialButtonChange = true;  // Button state changed for the first time, set initialButtonChange to true
      }
    }
    return;  // Skip the rest of the loop until initial button change occurs
  }

  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == HIGH && debounceActive == false) {
      changeMode();               // Button pressed, change the mode
      lastModeChange = millis();  // Record the timestamp of mode change
      debounceActive = true;      // Activate button debouncing
    }
  }

  if ((millis() - lastModeChange) > debounceDelay) {
    debounceActive = false;  // Disable button debouncing after debounceDelay
  }

  if (modeSelect == 0) {
    mode1();  // Execute mode 1 functionality
    delay(500);
  } else {
    mode2();  // Execute mode 2 functionality
  }
}


void changeMode() {
  if (modeSelect == 0) {
    modeSelect = 1;  // Toggle mode from 0 to 1
  } else {
    modeSelect = 0;  // Toggle mode from 1 to 0
  }
}

void mode1() {  // Glove Control Mode

  // Transmitter Code
  value1 = analogRead(flexPin1);
  value2 = analogRead(flexPin2);
  value3 = analogRead(flexPin3);
  value4 = analogRead(flexPin4);
  value5 = analogRead(flexPin5);

  flex1 = map(value1, 762, 861, 0, 180); // PINKY **
  flex1 = constrain(flex1, 0, 180); 

  flex2 = map(value2, 754, 836, 0, 180); // RING **
  flex2 = constrain(flex2, 0, 180);

  flex3 = map(value3, 806, 895, 0, 180); // THUMB ** *
  flex3 = constrain(flex3, 0, 180);

  flex4 = map(value4, 784, 876, 0, 180); // MIDDLE **
  flex4 = constrain(flex4, 0, 180);  

  flex5 = map(value5, 778, 875, 0, 180); // POINTER **
  flex5 = constrain(flex5, 0, 180);  

  transmit[0] = flex1;
  transmit[1] = flex2;
  transmit[2] = flex3;
  transmit[3] = flex4;
  transmit[4] = flex5;

  radio.write(&transmit, sizeof(transmit));  // This line of code is casuing the crash!?
   //get values to read on screen
  

  //get mode to read on screen.

  Serial.println("PINKY: " + String(transmit[0]));
  Serial.println("RING: " + String(transmit[1]));
  Serial.println("MIDDLE: " + String(transmit[2]));
  Serial.println("INDEX: " + String(transmit[3]));
  Serial.println("THUMB: " + String(transmit[4]));

  // Serial.println(flex1);
  // Serial.println(flex2);
  // Serial.println(flex3);
  // Serial.println(flex4);
  // Serial.println(flex5);
  //transmit[5] = modeSelect;
  delay(10);
}


void mode2() {  // Preset Gesture Mode

  Serial.println("LED is off");
  delay(10);
  transmit[5] = modeSelect;
  //*** Set transmit[] variable to preset motions and send them -- receiver code will run normally
}
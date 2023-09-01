#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

//ring pointer thumb
// Initialize Radio Data
RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";


int transmit[6];    // Data Array to be sent wirelessly
int checkIndex = 1; // Gesture Index

unsigned long interval = 1000;
unsigned long shortInterval = 750;
unsigned long longInterval = 3000;
unsigned long caseStartTime = 0;


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

void mode1() {  // Preset Gesture Mode 


  transmit[5] = 1;    
  
  switch (checkIndex){

    case 1:    // Fully Open
        delay(1000);
        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > shortInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 0;
        transmit[1] = 0;
        transmit[2] = 0;
        transmit[3] = 0;
        transmit[4] = 0;

      break;

    // case 2:    // Closed Trasnition 1

    //     if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > shortInterval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 5.5;
    //     transmit[2] = 18;
    //     transmit[3] = 37.5;
    //     transmit[4] = 120;

    //     break;

    // case 3:   // Closed Transition 2

    //      if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > shortInterval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 22.5;
    //     transmit[2] = 45;
    //     transmit[3] = 67.5;
    //     transmit[4] = 120;

    //   break;


    // case 4:  // Closed fist

    //    if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > interval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 95;
    //     transmit[1] = 120;
    //     transmit[2] = 85;
    //     transmit[3] = 80;
    //     transmit[4] = 115;

    //   break;

    // case 5:  // Open tranistion 1

    //    if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > shortInterval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 45;
    //     transmit[2] = 75;
    //     transmit[3] = 78;
    //     transmit[4] = 115;

    //   break;

    //   case 6:  // Open tranistion 2

    //    if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > shortInterval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 15;
    //     transmit[2] = 37.5;
    //     transmit[3] = 40;
    //     transmit[4] = 55;

    //   break;

    //    case 7:  // Open tranistion 3

    //    if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > shortInterval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 7.5;
    //     transmit[2] = 16;
    //     transmit[3] = 22;
    //     transmit[4] = 27.5;

    //   break;
    
    //  case 8:    // Fully Open

    //     if (caseStartTime == 0){
    //       caseStartTime = millis();
    //     }

    //     if (millis() - caseStartTime > interval){
    //         checkIndex++;
    //         caseStartTime = 0;
    //         break;
    //     }

    //     transmit[0] = 0;
    //     transmit[1] = 0;
    //     transmit[2] = 0;
    //     transmit[3] = 0;
    //     transmit[4] = 0;

    //   break;


      case 2:    // Peace Out!

        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > longInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 95;
        transmit[1] = 120;
        transmit[2] = 0;
        transmit[3] = 0;
        transmit[4] = 115;

      break;

      case 3:    // Rock On!

        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > longInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 0;
        transmit[1] = 120;
        transmit[2] = 90;
        transmit[3] = 0;
        transmit[4] = 115;

      break;


      case 4:    // Actually!

        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > longInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 95;
        transmit[1] = 120;
        transmit[2] = 90;
        transmit[3] = 0;
        transmit[4] = 115;

      break;


      case 5:    // Surfer Dude

        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > shortInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 0;
        transmit[1] = 120;
        transmit[2] = 95;
        transmit[3] = 0;
        transmit[4] = 0;
       

      break;

      case 6:    // surfer dude

        if (caseStartTime == 0){
          caseStartTime = millis();
        }

        if (millis() - caseStartTime > longInterval){
            checkIndex++;
            caseStartTime = 0;
            break;
        }

        transmit[0] = 0;
        transmit[1] = 120;
        transmit[2] = 95;
        transmit[3] = 90;
        transmit[4] = 0;
       

      break;


      // case 7:    // Middle Finger Raise

      //   if (caseStartTime == 0){
      //     caseStartTime = millis();
      //   }

      //   if (millis() - caseStartTime > longInterval){
      //       checkIndex++;
      //       caseStartTime = 0;
      //       break;
      //   }

      //   transmit[0] = 95;
      //   transmit[1] = 120;
      //   transmit[2] = 0;
      //   transmit[3] = 90;
      //   transmit[4] = 115;

      // break;




    default:
      checkIndex = 1;
      break;
  }

  radio.write(&transmit, sizeof(transmit));  
  delay(10);
  
  for(int i = 0; i < 5; i++){
    Serial.println("Transmitter" + String(transmit[i]));
  }
  Serial.println("test");

}


void mode2() {  // Glove Control Mode

  value1 = analogRead(flexPin1);
  value2 = analogRead(flexPin2);
  value3 = analogRead(flexPin3);
  value4 = analogRead(flexPin4);
  value5 = analogRead(flexPin5);

  flex1 = map(value1, 768, 861, 0, 180); // PINKY **
  flex1 = constrain(flex1, 0, 80); 

  flex2 = map(value2, 764, 819, 0, 180); // RING **  
  flex2 = constrain(flex2, 0, 95);

  flex3 = map(value3, 799, 868, 0, 180); // MIDDLE ** 
  flex3 = constrain(flex3, 0, 80);

  flex4 = map(value4, 784, 876, 0, 180); // INDEX **
  flex4 = constrain(flex4, 0, 85);  

  flex5 = map(value5, 818, 885, 0, 180); // THUMB ** 
  flex5 = constrain(flex5, 0, 115);  

  transmit[0] = flex1;
  transmit[1] = flex2;
  transmit[2] = flex3;
  transmit[3] = flex4;
  transmit[4] = flex5;
  transmit[5] = 2; 

  radio.write(&transmit, sizeof(transmit));  

  Serial.println("PINKY: " + String(transmit[0]));
  Serial.println("RING: " + String(transmit[1]));
  Serial.println("MIDDLE: " + String(transmit[2]));
  Serial.println("INDEX: " + String(transmit[3]));
  Serial.println("THUMB: " + String(transmit[4]));
  Serial.println("MODE: " + String(transmit[5]));

 
  delay(10);

}

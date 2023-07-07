  #include <RF24.h>
  #include <RF24_config.h>
  #include <nRF24L01.h>
  #include <printf.h>
  #include <Servo.h>
  #include <string.h>

  RF24 radio(7, 8); // CE, CSN

  const byte address[6] = "00001";  

  const int servoPin = 3;
  const int servoPin2 = 5;

  const int ARRAY_SIZE = 2;

  Servo myServo;
  Servo myServo2;
  //define variable to receive value
  int msg[ARRAY_SIZE];


  void setup() {
    Serial.begin(9600);
    Serial.println("test");
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    myServo.attach(servoPin);
    myServo2.attach(servoPin2);
  }

  void loop() {

    if (radio.available()) 
    {
    while (radio.available()){
      
      // radio.read(&value, sizeof(value));

      radio.read(&msg, sizeof(msg));
      //radio.read(&receivedString[1], strlen(receivedString[1]) + 1);

      // myServo.write(value/10);
      myServo.write(msg[0]);
      myServo2.write(msg[1]);

      Serial.println("MOTOR ONE: " + String(msg[0]));
      Serial.println("MOTOR TWO: " + String(msg[1]));
      delay(10);
    }

    }      
  }


  
  // Figure out why receiver is only getting 0 after being converted from string back to int.
  // Make sure it still gets random consistant values when sending just ints
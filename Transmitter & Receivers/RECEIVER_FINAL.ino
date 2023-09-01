  #include <RF24.h>
  #include <RF24_config.h>
  #include <nRF24L01.h>
  #include <printf.h>
  #include <Servo.h>
  #include <string.h>

  RF24 radio(7, 8); // CE, CSN
  const byte address[6] = "00001";  

  const int servoPin1 = 3;
  const int servoPin2 = 5;
  const int servoPin3 = 6;
  const int servoPin4 = 9;
  const int servoPin5 = 10;

  Servo myServo1;
  Servo myServo2;
  Servo myServo3;
  Servo myServo4;
  Servo myServo5;

  //define variable to receive value
  int data[6];

  void setup() {
    Serial.begin(9600);
    Serial.println("test");
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    myServo1.attach(servoPin1);
    myServo2.attach(servoPin2);
    myServo3.attach(servoPin3);
    myServo4.attach(servoPin4);
    myServo5.attach(servoPin5);

    myServo1.write(0);
    myServo2.write(0);
    myServo3.write(0);
    myServo4.write(0);
    myServo5.write(0);
  }

  void loop() {

    if (radio.available()) 
    {
    while (radio.available()){

      radio.read(&data, sizeof(data));

      Serial.write((byte*)&data, sizeof(data)); 

      myServo1.write(data[0]);
      myServo2.write(data[1]);
      myServo3.write(data[2]);
      myServo4.write(data[3]);
      myServo5.write(data[4]);

      Serial.println("MOTOR PINKY: " + String(data[0]));
      Serial.println("MOTOR RING: " + String(data[1]));
      Serial.println("MOTOR MIDDLE: " + String(data[2]));
      Serial.println("MOTOR INDEX: " + String(data[3]));      
      Serial.println("MOTOR THUMB: " + String(data[4]));
      Serial.println("Mode: " + String(data[5]));
      delay(10);
    }

    }      
  }

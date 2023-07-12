#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//TFT DC & CS PINS
#define TFT_DC 9
#define TFT_CS 10

//Wired Communcation
int data[5];

//Setting up SPI with defined DC & CS PINS
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() {
  Serial.begin(9600);
  tft.begin();

}


void loop() {
  //rotate screen & loading screen
  for (int rotation = 0; rotation < 4; rotation++){
    tft.setRotation(rotation);
    testTriangles();
  }
  
  //Set Horizontal + Welcome Screen
  tft.setRotation(3);
  welcomeScreen(); //15 second delay intermission
 

  gloveInterface();
}


///////////////////// Triangle Graphics.  ///////////////////////////////
void testTriangles() {
  int n, i;
  int cx = tft.width()  / 2 - 1;
  int cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx, cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  delay(1000);
}


////////////////////  Author Documentation  ///////////////////////////
void welcomeScreen(){
  // TextSize(1) Width:6, Height:8 (increase size is multiples by size factor)

  // String Setup
  const String title = "Welcome to MCC!";
  const String authorList = "Created by";
  const String Cameron = "Cameron Bauman";
  const String Chase = "Chase Keeler";
  const String Matthew = "Matthew Salazar";

  // Center Coordinates
  int16_t titleWidth = title.length() * 18; // Pixel Width: 18, Pixel Height: 24
  int16_t titleX = (tft.width() - titleWidth) / 2;
  int16_t titleY = (tft.height() / 2) - 30;

  int16_t authorWidth = authorList.length() * 12; // Pixel Width: 12, Pixel Height: 8
  int16_t authorX = (tft.width() - authorWidth) / 2;
  int16_t authorY = (tft.height() / 2) + 10;

  // Set Background
  tft.fillScreen(ILI9341_BLACK);

  // Title
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(titleX, titleY);
  tft.println(title);

  //Created By
  tft.setTextSize(2);

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(authorX, centerTextHeight(0));
  tft.println(authorList);

  //Cameron
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(Cameron,12), centerTextHeight(20));
  tft.println(Cameron);

  //Chase
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(Chase,12), centerTextHeight(40));
  tft.println(Chase);

  //Matthew
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(Matthew,12), centerTextHeight(60));
  tft.println(Matthew);

  delay(5000);
}


/////////////////////////// Display flex sensors values ///////////////////
void gloveInterface() {
  // Set Strings
  tft.fillScreen(ILI9341_BLACK);
  String thumb = "Thumb: ";
  String index = "Index: ";
  String middle = "Middle: ";
  String ring = "Ring: ";
  String pinky = "Pinky: ";

  // Clear initial offline status
  tft.fillRect(80, 10, 80, 20, ILI9341_BLACK);
  
  while (true) {
    if (Serial.available()) {
      // Read the received data
      int receivedData[5];
      Serial.readBytes((byte*)receivedData, sizeof(receivedData));

      // SYSTEM ONLINE
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_WHITE);
      tft.print("System: ");
      tft.setTextColor(ILI9341_GREEN);
      tft.print("ONLINE");
      
      // Clear region for updated data
      tft.fillRect(195, centerTextHeight(-40) - 10, 40, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(-20) - 10, 40, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(0) - 10, 40, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(20) - 10, 40, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(40) - 10, 40, 30, ILI9341_BLACK);

      // Thumb
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(thumb, 12), centerTextHeight(-40));
      tft.println(thumb + String(receivedData[0]));

      // Index
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(index, 12), centerTextHeight(-20));
      tft.println(index + String(receivedData[1]));

      // Middle
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(middle, 12), centerTextHeight(0));
      tft.println(middle + String(receivedData[2]));

      // Ring
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(ring, 12), centerTextHeight(20));
      tft.println(ring + String(receivedData[3]));

      // Pinky
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(pinky, 12), centerTextHeight(40));
      tft.println(pinky + String(receivedData[4]));
    }
    else {
      tft.fillRect(90, 10, 100, 20, ILI9341_BLACK);
      tft.setCursor(100, 10);
      tft.setTextColor(ILI9341_RED);
      tft.print("OFFLINE");
      
      // Clear previous data
      tft.fillRect(195, centerTextHeight(-40) - 10, 40, 70, ILI9341_BLACK);
    }
  }
}
  

   


//////////////////////// Center Text Functions  //////////////////////
int16_t centerTextWidth(String name, int pixelWidth){ 
  int16_t textWidth = name.length() * pixelWidth;
  return (tft.width() - textWidth) / 2;
}

//Center Text Height
int16_t centerTextHeight(int height){
  return (tft.height() / 2) + height;
}

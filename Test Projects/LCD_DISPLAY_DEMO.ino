#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//TFT DC & CS PINS
#define TFT_DC 9
#define TFT_CS 10

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

    if (rotation == 3){
      break;
    }
  }
  
  //Set Horizontal + Welcome Screen
  tft.setRotation(3);
  welcomeScreen();
 
  while (true){
    gloveInterface();
  }
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
  int16_t titleY = (tft.height() / 2) - 20;

  int16_t authorWidth = authorList.length() * 6; // Pixel Width: 6, Pixel Height: 8
  int16_t authorX = (tft.width() - authorWidth) / 2;
  int16_t authorY = (tft.height() / 2) + 10;

  // Set Background
  tft.fillScreen(ILI9341_BLACK);

  // Title
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(titleX, titleY);
  tft.println(title);

  //Created By
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(authorX, centerTextHeight(10));
  tft.println(authorList);

  //Cameron
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(centerTextWidth(Cameron,6), centerTextHeight(20));
  tft.println(Cameron);

  //Chase
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(centerTextWidth(Chase,6), centerTextHeight(30));
  tft.println(Chase);

  //Matthew
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(centerTextWidth(Matthew,6), centerTextHeight(40));
  tft.println(Matthew);

  delay(15000);
}


/////////////////////////// Display flex sensors values ///////////////////
void gloveInterface(){
  //Set Strings
  String thumb = "Thumb: 25";
  String index = "Index: 25";
  String middle = "Middle: 25";
  String ring = "Ring: 25";
  String pinky = "Pinky: 25";


  //Center Coordinates
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(2);

  //Thumb
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(thumb,12), centerTextHeight(-40));
  tft.println(thumb);

  //Index
   tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(index,12), centerTextHeight(-20));
  tft.println(index);
  
  //Middle
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(middle,12), centerTextHeight(0));
  tft.println(middle);

  //Ring
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(ring,12), centerTextHeight(20));
  tft.println(ring);

  //Pinky
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(centerTextWidth(pinky,12), centerTextHeight(40));
  tft.println(thumb);
 
  delay(100000);
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
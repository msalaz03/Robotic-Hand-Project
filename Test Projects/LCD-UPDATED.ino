#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//TFT DC & CS PINS
#define TFT_DC 9
#define TFT_CS 10

//global variables to prevent overriding of connection status.
boolean stopLoop = false;
boolean previousStatus = false;
static int previousMode = -1;

//Setting up SPI with defined DC & CS PINS
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() {
  Serial.begin(9600);
  tft.begin();
  

}


void loop() 
{
  //rotate screen & loading screen
  for (int rotation = 0; rotation < 4; rotation++)
  {
    tft.setRotation(rotation);
    testTriangles();
  }

  tft.setRotation(3);   //Set Horizontal + Welcome Screen
  welcomeScreen();  //15 second delay intermission
  gloveInterface();
}


//triangle graphics
void testTriangles() 
{
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


//author documentation
void welcomeScreen()
{
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


//flex sensor values + main screen
void gloveInterface() 
{
  String thumb = "Thumb: "; 
  String index = "Index: "; 
  String middle = "Middle: ";
  String ring = "Ring: "; 
  String pinky = "Pinky: ";

  int receivedData[5];  //flex sensor values
  bool receivedMode = false; //mode 1 or 2

  tft.fillScreen(ILI9341_BLACK);  //reset screen
  unsigned long offlineTime = 0; //time buffer

 while (true) 
 {  
    if (Serial.available()) 
    {
      // Read the received data
      Serial.readBytes((byte*)receivedData, sizeof(receivedData));

      if (Serial.available() >= sizeof(bool)) {
        byte boolByte = Serial.read();
        receivedMode = boolByte;
      }

      // SYSTEM ONLINE
      if(!previousStatus)
      {
        systemconnection(true);
      }

       modeDisplay(receivedMode,previousMode);
      
      //print string values
      tft.fillRect(195, centerTextHeight(-40) - 10, 60, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(-20) - 10, 60, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(0) - 10, 60, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(20) - 10, 60, 20, ILI9341_BLACK);
      tft.fillRect(195, centerTextHeight(40) - 10, 60, 30, ILI9341_BLACK);

      // Thumb
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(thumb, 12), centerTextHeight(40));
      tft.println(thumb + String(receivedData[0]/256));

      // Index
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(index, 12), centerTextHeight(-40));
      tft.println(index + String(receivedData[1]/256));

      // Middle
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(middle, 12), centerTextHeight(-20));
      tft.println(middle + String(receivedData[2]/256));

      // Ring
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(ring, 12), centerTextHeight(0));
      tft.println(ring + String(receivedData[3]/256));

      // Pinky
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(centerTextWidth(pinky, 12), centerTextHeight(20));
      tft.println(pinky + String(receivedData[4]/256));
      delay(100);
      offlineTime = millis();
    }
    else
    {
      if (!stopLoop && (millis() - offlineTime > 300))
      {
        systemconnection(false);
      }
      
    }
    Serial.println(receivedMode);
    previousMode = receivedMode;
   
    
  
  }
}


//display user or automated mode
void modeDisplay(int mode, int previousMode)
{
  if (previousMode == mode){
    return;
  }
  
  String userON = "USER CONTROL: ON";
  String userOFF  = "USER CONTROL: OFF";

  tft.fillRect(centerTextWidth(userOFF,12), centerTextHeight(60) + 10, 200, 25, ILI9341_BLACK);
  tft.setCursor(centerTextWidth(userOFF,12), centerTextHeight(60) + 10);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  

  //user control
  if (mode == 1)
  {
    tft.println(userON);
  }
  else if(mode == 0)
  {
    tft.println(userOFF);
  }
}

//connection status
void systemconnection(boolean online)
{
    int maxStringLength = 250; //String Pixel Width
    int maxStringWidth = 16; //String Pixel Height
    tft.setCursor(50,50);

    if (online){
      //status online
      if(!previousStatus){
        tft.fillRect(50, 50, maxStringLength, maxStringWidth, ILI9341_BLACK);
        delay(10);
        tft.setTextColor(ILI9341_WHITE);
        tft.print("CONNECTION: ");
        tft.setTextColor(ILI9341_GREEN);
        tft.print("ONLINE");
        previousStatus = true;
        stopLoop = false;
      }
     
    }
    else if (!online){
      //status online
      if(previousStatus && !stopLoop){
        tft.fillRect(50, 50, maxStringLength, maxStringWidth, ILI9341_BLACK);
        delay(10);
        previousStatus = false;
        stopLoop = true;
        tft.setTextColor(ILI9341_WHITE);
        tft.print("CONNECTION: ");
        tft.setTextColor(ILI9341_RED);
        tft.print("OFFLINE");
      }
      
    }

}

//center text width 
int16_t centerTextWidth(String name, int pixelWidth)
{ 
  int16_t textWidth = name.length() * pixelWidth;
  return (tft.width() - textWidth) / 2;
}

//center text height
int16_t centerTextHeight(int height)
{
  return (tft.height() / 2) + height;
}

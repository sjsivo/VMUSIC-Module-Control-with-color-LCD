/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  The 1.14" TFT breakout
  ----> https://www.adafruit.com/product/4383
  The 1.3" TFT breakout
  ----> https://www.adafruit.com/product/4313
  The 1.54" TFT breakout
    ----> https://www.adafruit.com/product/3787
  The 2.0" TFT breakout
    ----> https://www.adafruit.com/product/4311
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
//#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerifItalic9pt7b.h>
#include <SPI.h>


  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        22
  #define TFT_RST        18 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         21
// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_MOSI 23  // Data out
#define TFT_SCLK 19  // Clock out

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC,TFT_MOSI,TFT_SCLK ,TFT_RST);

// For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);




// For ST7735-based displays, we will use this call
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// OR for the ST7789-based displays, we will use this call
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float p = 3.1415926;
#include <EasyButton.h>

// Arduino pin where the buttons are connected to
#define BUTTON_ONE_PIN 13
#define BUTTON_TWO_PIN 0
#define BUTTON_THREE_PIN 32
#define BUTTON_FOUR_PIN 33
// Button1
EasyButton button1(BUTTON_ONE_PIN);
// Button2
EasyButton button2(BUTTON_TWO_PIN);
// Button3
EasyButton button3(BUTTON_THREE_PIN);
// Button4
EasyButton button4(BUTTON_FOUR_PIN);
// Callback function to be called when button1 is pressed
void onButton1Pressed() {
  Serial.println("Button1 has been pressed!");
  Serial2.print(F("VSB\r"));
}

// Callback function to be called when button2 is pressed
void onButton2Pressed() {
  Serial.println("Button2 has been pressed!");
  Serial2.print(F("VSF\r"));
}

// Callback function to be called when button3 is pressed
void onButton3Pressed() {
  Serial.println("Button3 has been pressed!");
  Serial2.print(F("VP\r"));
}

// Callback function to be called when button4 is pressed
void onButton4Pressed() {
  Serial.println("Button4 has been pressed!");
  Serial2.print(F("VF\r"));
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void setup(void) {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  //Serial2.print(F("FWU V2MSC.ROM\r"));
Serial2.print(F("VSV $00\r"));
//Serial2.print(char(0));
//Serial2.print("\r");
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
tft.setRotation(1);
  // OR use this initializer (uncomment) if using a 1.44" TFT:
  //tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab

  // OR use this initializer (uncomment) if using a 0.96" 160x80 TFT:
  //tft.initR(INITR_MINI160x80);  // Init ST7735S mini display

  // OR use this initializer (uncomment) if using a 1.3" or 1.54" 240x240 TFT:
  //tft.init(240, 240);           // Init ST7789 240x240

  // OR use this initializer (uncomment) if using a 2.0" 320x240 TFT:
  //tft.init(240, 320);           // Init ST7789 320x240

  // OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
  //tft.init(135, 240);           // Init ST7789 240x135

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
Serial2.print(F("VRR\r"));//V3A
  // Initialize the button1
  button1.begin();
  // Initialize the button2
  button2.begin();
  // Initialize the button3
  button3.begin();
  // Initialize the button4
  button4.begin();
  // Add the callback function to be called when the button1 is pressed.
  button1.onPressed(onButton1Pressed);
  // Add the callback function to be called when the button2 is pressed.
  button2.onPressed(onButton2Pressed);
  // Add the callback function to be called when the button3 is pressed.
  button3.onPressed(onButton3Pressed);
  // Add the callback function to be called when the button4 is pressed.
  button4.onPressed(onButton4Pressed);
  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Sktechnologie 2020 Sivak", ST77XX_BLUE);
  //delay(1000);
/*
  // tft print function!
  tftPrintTest();
  delay(4000);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);
*/
  Serial.println("done");
  
  delay(1000);
}
String received="";
int beforetime=0;
String beforefile="";
String beforesong="";
String beforeinterpret="";
String beforealbum="";
void loop() {
   // Continuously read the status of the buttons
  button1.read();
  button2.read();
  button3.read();
  button4.read();
received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("T ") >=0)
  break;
  if (received.indexOf("Playing ") >=0)
  break;
if (received.indexOf("No Disk") >=0)
  break;
  if (received.indexOf("Device Detected ") >=0)
  break;
  }
  Serial.print(received);

  if (received.indexOf("No Disk") >=0)
  {
    tft.setFont(&FreeSerifItalic9pt7b);
    tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforefile);
    tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.print("Neni USB!!!");
  beforefile="Neni USB!!!";
  }

  if (received.indexOf("Device Detected ") >=0)
  {
    tft.setFont(&FreeSerifItalic9pt7b);
    tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforefile);
    tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(0x07FF);
  tft.setTextSize(1);
  tft.print("Citam USB...");
  beforefile="Citam USB...";
  Serial2.print(F("V3A\r"));
  }
  if (received.indexOf("T ") >=0)
  {
    
    
    tft.setFont(&FreeSans12pt7b);
    tft.setCursor(15, 70);
  //tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
 
//int tt=t1+t2;
  if (beforetime/60<10) tft.print("0");
  tft.print(beforetime/60,DEC);
  tft.print(":");
  if (beforetime%60<10) tft.print("0");
  tft.print(beforetime%60,DEC);
  tft.setCursor(15, 70);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  char t1=char(Serial2.read());
  char t2=char(Serial2.read());
  int tt=t1+(t2*256);
  if (tt/60<10) tft.print("0");
  tft.print(tt/60,DEC);
  tft.print(":");
  if (tt%60<10) tft.print("0");
  tft.print(tt%60,DEC);
  beforetime=tt;
  }
  if (received.indexOf("Playing ") >=0)
  {
    received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("\r") >=0)
  break;
  }
  tft.setFont(&FreeSerifItalic9pt7b);
  tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforefile);
    tft.setCursor(15, 30);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(0x07FF);
  tft.setTextSize(1);
  tft.print(received);
  beforefile=received;
  //---------------
      received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("\r") >=0)
  break;
  }
  //no track num need...
    received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("\r") >=0)
  break;
  }
   tft.setCursor(15, 90);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforesong);
    tft.setCursor(15, 90);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(0x07FF);
  tft.setTextSize(1);
  tft.print(received);
  beforesong=received;

 // ----------------

    received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("\r") >=0)
  break;
  }
   tft.setCursor(15, 104);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforeinterpret);
    tft.setCursor(15, 104);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(0x07FF);
  tft.setTextSize(1);
  tft.print(received);
  beforeinterpret=received;

  received="";
   while (Serial2.available()) {
    received=received+char(Serial2.read());
    if (received.indexOf("\r") >=0)
  break;
  }
   tft.setCursor(15, 118);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.print(beforealbum);
    tft.setCursor(15, 118);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(0x07FF);
  tft.setTextSize(1);
  tft.print(received);
  beforealbum=received;
  }
 // tft.invertDisplay(true);
 // delay(100);
 // tft.invertDisplay(false);
 // delay(100);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}



void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 48, 40, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 40, 45, 20, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 40, 45, 20, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 40, 45, 20, ST77XX_GREEN);
}

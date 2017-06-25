/*
 * GuiPittix simple graphical user interface elemetns
 * 
 * Hardware:
 *  TFT: SDFP5408 Arduino Shield with parallel interface
 *  http://www.ebay.de/itm/2-4-TFT-LCD-Display-Shield-Touch-Panel-ILI9341-240X320-for-Arduino-UNO-MEGA-/382052804437
 *  Library https://github.com/JoaoLopesF/SPFD5408
 *  MCU: Arduino Uno
 *
 * 2017, ChrisMicro
 * 
 */
//#include "SPI.h"
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include "colors.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

Adafruit_TFTLCD * Display;


/*****************************************************************************************
 * GuiPittix Classes
 ****************************************************************************************/
// For the Adafruit shield, these are the default.

class GUI_Object
{
  public:
    uint16_t x, y, w, h;
    uint16_t color;
    uint16_t colorBackground;
    static uint16_t xNext, yNext;
    uint8_t textSize;

    GUI_Object()
    {
      textSize = 2;
      x = xNext;
      y = yNext;
      w = 30 * textSize; // 5x8
      h = 16 * textSize;
      yNext += h;
      color           = COLOR_RED;
      colorBackground = COLOR_BLACK;
    };

    void setColor(uint16_t c)
    {
      color=c;
    }
    
    void show()
    {
      Display->fillRect(x, y, w, h, colorBackground);
      Display->drawRect(x, y, w, h, color);
      Display->setCursor(x + w, y);
    }

};

uint16_t GUI_Object::yNext = 5;
uint16_t GUI_Object::xNext = 5;

class GUI_Led : public GUI_Object
{
  public:
    int xx, yy, rr;
    int xxText,yyText;
    char * ledName;

    GUI_Led(char * txt)
    {
      ledName = txt;
      int textOffset = (strlen(txt)+2) * 5 * textSize;

      xxText = x ;
      xx     = textOffset + h / 2 + 1;
      yyText = y ;
      yy = yyText + h / 2 + 1;
      rr = h / 2 - 2;
    }

    GUI_Led()
    {
      GUI_Led: GUI_Led("");
    }
    
    void showLabel()
    {
      Display->setTextColor(COLOR_GREEN);
      Display->setCursor(xxText,yy);
      Display->print(ledName);
    }
    
    void on()
    {
      showLabel();
      Display -> fillCircle(xx, yy, rr, COLOR_GREY);
      Display -> fillCircle(xx , yy , rr - 4, color);
    }

    void off()
    {
      showLabel();
      Display -> fillCircle(xx, yy, rr, COLOR_GREY);
      Display -> fillCircle(xx , yy , rr - 4, colorBackground);
    }
};

/*****************************************************************************************
 * Arduino program
 ****************************************************************************************/

GUI_Led   Led1("up  ");
GUI_Led   Led2("down");

void setup()
{
  //tft.begin();
  tft.begin(0x9341); // SDFP5408
  tft.fillScreen(LTDC_BLACK);
  tft.setRotation(1); 

  Display = &tft;
  
  Led1.setColor(COLOR_GREEN);
}

void loop(void)
{
  Led1.on();
  Led2.off();
  delay(1000);
  Led1.off();
  Led2.on();
  delay(1000);
}

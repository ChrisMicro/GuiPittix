/*
 * GuiPittix simple graphical user interface elemetns
 * 
 * Hardware:
 *  TFT: ILI9341 with SPI
 *  MCU: STM32F103 BluePill
 * 
 */
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "colors.h"

#define TFT_DC   PA2
#define TFT_RST  PA3
#define TFT_CS   PA4

#define TFT_CLK  PA5
#define TFT_MISO PA6
#define TFT_MOSI PA7

// Use hardware SPI 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

Adafruit_ILI9341 * Display;


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

Adafruit_ILI9341 * Display; // this pointer is needed from the GUI driver

GUI_Led   Led1("up  ");
GUI_Led   Led2("down");

void setup()
{
  tft.begin();
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











/* GuiPittix simple graphical user interface elemetns
 *   
 * © ChrisMicro 2017.
 *
 * This file is part of GuiPittix.
 *
 * GuiPittix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GuiPittix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.
 *
 * If you use simple_GUI_elements in public project you can inform me about this by e-mail,
 * of course if you want it.
 *
 * web-site: https://github.com/ChrisMicro/GuiPittix
 */


/* 
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   2017, ChrisMicro
*/

#ifndef _GUI_
#define _GUI_
#include "TFT_Adapter.h"

TFT_Adapter tft;

/*****************************************************************************************
 * GuiPittix Classes
 ****************************************************************************************/
// For the Adafruit shield, these are the default.

class Gui
{
  public:
  void begin()
  {
      tft.begin();
      tft.fillScreen(COLOR_BLACK);
  }
};

Gui gui;

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
      textSize = 3;
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
      tft.fillRect(x, y, w, h, colorBackground);
      tft.drawRect(x, y, w, h, color);
      tft.setCursor(x + w, y);
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
      tft.setTextColor(COLOR_GREEN);
      tft.setCursor(xxText,yy);
      tft.print(ledName);
    }
    
    void on()
    {
      showLabel();
      tft.fillCircle(xx, yy, rr, COLOR_GREY);
      tft.fillCircle(xx , yy , rr - 4, color);
    }

    void off()
    {
      showLabel();
      tft.fillCircle(xx, yy, rr, COLOR_GREY);
      tft.fillCircle(xx , yy , rr - 4, colorBackground);
    }
};

#endif

/* GuiPittix simple graphical user interface elemetns

   © ChrisMicro 2017.

   This file is part of GuiPittix.

   GuiPittix is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GuiPittix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.

   If you use simple_GUI_elements in public project you can inform me about this by e-mail,
   of course if you want it.

   web-site: https://github.com/ChrisMicro/GuiPittix
*/

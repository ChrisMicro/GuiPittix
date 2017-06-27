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

// standard text size 5x8

// layout manager
#define LAYOUT_TILE_WIDTH  30
#define LAYoUT_TILE_HEIGTH 16

class GUI_Object
{
  public:
    uint16_t x, y, w, h;
    uint16_t color;
    uint16_t colorBackground;
    static uint16_t layoutNext_x, layoutNext_y;
    uint8_t textSize; // 1,2,3 ..

    void init()
    {
      textSize = 3;
      x = layoutNext_x;
      y = layoutNext_y;
      w = LAYOUT_TILE_WIDTH  * textSize; 
      h = LAYoUT_TILE_HEIGTH * textSize;
      layoutNext_y += h + textSize;
      color           = COLOR_RED;
      colorBackground = COLOR_BLACK;   
    }

    GUI_Object()
    {
      init();
    };
    
    GUI_Object(uint16_t posX,uint16_t posY)
    {

      layoutNext_x = posX;
      layoutNext_y = posY;
      
      init();
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

// LayoutManager 
// start position for first object
uint16_t GUI_Object::layoutNext_y = 5;
uint16_t GUI_Object::layoutNext_x = 5;

/*

labeledObject consists of a name and a graphic

*/

class GUI_labeledObject: public GUI_Object
{
  public:
    char * objectName;
    
    int ElementX,ElementY;
    int ElementW,ElementH;
    
    int TextPosY;

    void init(char * txt)
    {
      x = layoutNext_x;
      y = layoutNext_y;
      
      objectName = txt;
      int textOffset = (strlen(txt)+2) * 5 * textSize;

      ElementW = LAYOUT_TILE_WIDTH  * textSize;
      ElementH = h;
      
      int offset = textOffset + 1;
      
      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y;
      
      TextPosY = y + h / 2 + 1;    
    }
    
    GUI_labeledObject(char * txt)
    {
      init(txt);
    }
    
    GUI_labeledObject(uint16_t posX,uint16_t posY,char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(textSize);
      tft.setCursor(x,TextPosY);
      tft.print(objectName);
    }
    
    void show()
    {
      showLabel();
      //GUI_Object::show();
      tft.drawRect(x, y, w, h, COLOR_GREY);
      tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED);      
    }

	
};


class GUI_Led : public GUI_Object
{
  public:
    char * objectName;
    
    int ElementX,ElementY;
    int ElementW,ElementH;
    
    int TextPosY;
    
    int xx, yy, rr;


    void init(char * txt)
    {
      x = layoutNext_x;
      y = layoutNext_y;
      
      objectName = txt;
      int textOffset = (strlen(txt)+2) * 5 * textSize;

      //ElementW = LAYOUT_TILE_WIDTH  * textSize;
      ElementH = w;
      ElementH = h;
      
      int offset = textOffset + 1;
      
      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y;
      
      TextPosY = y + h / 2 + 1;    
      
      rr = h / 2 - 2;
      xx = ElementX + h/2;
      yy = ElementY + h/2;
    }
    
    GUI_Led(char * txt)
    {
      init(txt);
    }
    
    GUI_Led(uint16_t posX,uint16_t posY,char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(textSize);
      tft.setCursor(x,TextPosY);
      tft.print(objectName);
    }
    
    void show()
    {
      showLabel();
      //GUI_Object::show();
      //tft.drawRect(x, y, w, h, COLOR_GREY);
      //tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED);      
    }  
    
    void on()
    {
      showLabel();
      //tft.drawRect(x, y, w, h, COLOR_GREY);
      //tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED); 
      tft.fillCircle(xx, yy, rr, COLOR_GREY);
      tft.fillCircle(xx, yy, rr - 4, color);
    }

    void off()
    {
      showLabel();
      tft.fillCircle(xx, yy, rr, COLOR_GREY);
      tft.fillCircle(xx , yy , rr - 4, colorBackground);
    }
};

/*
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
      tft.setTextSize(textSize);
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
*/
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

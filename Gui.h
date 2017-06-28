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

int TouchX,TouchY,ScreenTouched;



class Gui
{
  public:
  void begin()
  {
      tft.begin();
      tft.fillScreen(COLOR_BLACK);

      
  }
  
  // tell the gui the finger coordinates
  // or mouse position
  // the coordinates can be used by the "isHit" function
  void setTouch(int x,int y,int z)
  {
    TouchX=x;
    TouchY=y;
    ScreenTouched=z;
  }
};



Gui gui;



// standard text size 5x8

// layout manager
#define LAYOUT_TILE_WIDTH  30
#define LAYOUT_TILE_HEIGTH 16
// standard font
#define FONT_WIDTH 5
#define FONT_HEIGTH 8

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
      textSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;
      w = LAYOUT_TILE_WIDTH  * textSize; 
      h = LAYOUT_TILE_HEIGTH * textSize;
      
      layoutNext_y += h + textSize;
      
      color           = COLOR_BLUE;
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
    
    // just check if the mouse points to the object
    boolean isHit()
    {
      boolean flag = false;
      if ( TouchX > x && TouchX < x + w && TouchY > y && TouchY < y + h ) flag = true;
      return flag;
    }
    
    // is the mouse button pressed?
    boolean isPressed()
    {
      boolean flag = isHit() && (ScreenTouched != 0 );
      return flag;      
    }

};

// LayoutManager 
// start position for first object
uint16_t GUI_Object::layoutNext_y = 5;
uint16_t GUI_Object::layoutNext_x = 5;

#define BUTTON_OFF_COLOR   COLOR_GREY/3*2
#define BUTOON_ON_COLOR    COLOR_WHITE
#define BUTTON_TEXT_COLOR  COLOR_BLUE

class GUI_Button: public GUI_Object
{
  public:
  
  char * buttonName;
  uint8_t state=0;
  
  uint16_t textPosX,textPosY;

  
    void init(char * txt)
    {
      buttonName=txt;  
      textSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;
      
      w=(strlen(buttonName)+1)*(FONT_WIDTH+1) * textSize;

      h = LAYOUT_TILE_HEIGTH * textSize;
      
      textPosY      = y+h/2-FONT_HEIGTH;
      textPosX      = x + (FONT_WIDTH/2)*textSize;
      
      layoutNext_y += 2*textSize;
      
      color           = BUTTON_OFF_COLOR;
      colorBackground = COLOR_BLACK;

    }
    
    GUI_Button(char * txt)
    {  
      init(txt);
    }
    
    GUI_Button(uint16_t posX,uint16_t posY,char * txt)
    {
      layoutNext_x=posX;
      layoutNext_y=posY;
      init(txt);    
    }
    
    void show()
    {
	
      tft.fillRoundRect(x, y, w, h, 5,color);
  
      //tft.setCursor(x+2*textSize, y+ 1*textSize);
      tft.setCursor(textPosX, textPosY);

      tft.setTextColor( BUTTON_TEXT_COLOR );
      tft.print(buttonName);	    
    }
    
     boolean wasPressed()
    {
      boolean wasPressed_flag = false;
      switch (state)
      {
        case 0:
          {
            if (isHit())
	    {
		color=BUTOON_ON_COLOR;
		state = 1;    
	    }		    
          } break;
        case 1:
          {
            if (!isHit())
            {
		color=BUTTON_OFF_COLOR;
              state = 0;
              wasPressed_flag = true;
            }
          } break;

      }
      show();
      return wasPressed_flag;
}
    
};





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
    
    boolean ledState=false;


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
    
    void setLed(boolean offOn)
    {
	if(ledState)on();
	else off();	
    }
    void toggle()
    {
	ledState=!ledState;
	setLed(ledState);	
    }
    
};



class GUI_Number: public GUI_Object
{
  public:
    char * objectName;
    
    int ElementX,ElementY;
    int ElementW,ElementH;
    
    int TextPosY;
    
    int number=0;

    void init(char * txt)
    {
      w=( FONT_WIDTH + 2 ) * textSize;
      h=( FONT_HEIGTH + 2 ) * textSize;      
      x = layoutNext_x;
      y = layoutNext_y;
      
      objectName = txt;
      int textOffset = (strlen(txt)+2) * 5 * textSize;

      //ElementW = LAYOUT_TILE_WIDTH  * textSize; 
      
      ElementW = (10+ 1 ) * FONT_WIDTH * textSize; //10 digits
      ElementH = h;
      
      int offset = textOffset + 1;
      
      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y ;
      
      //TextPosY = y + h / 2 + 1;
      TextPosY = y+1*textSize;      
    }
    
    GUI_Number(char * txt)
    {
      init(txt);
    }
    
    GUI_Number(uint16_t posX,uint16_t posY,char * txt)
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
      // label frame
      //tft.drawRect(x, y, w, h, COLOR_GREY);
      tft.fillRect(ElementX, ElementY, ElementW, ElementH, COLOR_GREY);
      //tft.fillRect(ElementX, ElementY, ElementW, ElementH, colorBackground);
  
      tft.setCursor(ElementX+2*textSize, ElementY+ 1*textSize);
      tft.setTextColor(color);
      tft.print(number);
      //number frame
      //tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED);      
    }

    void print(int num)
    {
       number=num;
       show();       
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

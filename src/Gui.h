/*
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   2017-2019, ChrisMicro
*/

#ifndef _GUI_
#define _GUI_
#include "TFT_Adapter.h"

TFT_Adapter tft;

/*****************************************************************************************
   GuiPittix Classes
 ****************************************************************************************/
// For the Adafruit shield, these are the default.

int TouchX, TouchY, ScreenTouched;



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
    void setTouch(int x, int y, int z)
    {
      TouchX = x;
      TouchY = y;
      ScreenTouched = z;
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

/*
GUI_Object

The base object of all elemetns.
It has a position, colors and if the touch variables are set before
you can easily detect if the object is hit or pressed.
This is useful for making elements like buttons.

*/
class GUI_Object
{
  public:
    uint16_t x, y, w, h;
    uint16_t color;
    uint16_t colorBackground;
    static uint16_t layoutNext_x, layoutNext_y;
    uint8_t guiSize; // 1,2,3 ..

    void init()
    {
      guiSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;
      w = LAYOUT_TILE_WIDTH  * guiSize;
      h = LAYOUT_TILE_HEIGTH * guiSize;

      //layoutNext_y += h + guiSize;

      color           = COLOR_BLUE;
      colorBackground = COLOR_BLACK;
    }

    GUI_Object()
    {
      init();
    };

    GUI_Object(uint16_t posX, uint16_t posY)
    {

      layoutNext_x = posX;
      layoutNext_y = posY;

      init();
    };

    void setColor(uint16_t c)
    {
      color = c;
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
// coerce an integer into its limits
int coerce(int value,int min, int max)
{
    if(value>max)value=max;
    if(value<min)value=min;    
    return value;
}

class GUI_Slider : public GUI_Object
{
  public:

    char *   sliderName;
    uint16_t namePosY;
    uint8_t nameHeight;
    uint16_t sliderPosY;
    uint16_t sliderHeight;
    uint16_t sliderIndicatorPosY;
    uint8_t  sliderIndicatorHeight;
    int32_t sliderValue;
    uint8_t sliderPOintRadius;
    uint16_t sliderPointPosY;

    void init(char * txt)
    {
      sliderName = txt;
      guiSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;
      namePosY = y;
      w = FONT_WIDTH * 5  * guiSize;

      nameHeight = (FONT_HEIGTH + 3) * guiSize;

      sliderPOintRadius = nameHeight / 2 - 2;

      sliderPosY   = y + nameHeight ;
      sliderHeight = 150;
      sliderPointPosY = sliderPosY + sliderHeight / 2;
      sliderIndicatorPosY = sliderPosY + sliderHeight;
      sliderIndicatorHeight = nameHeight;

      layoutNext_x += w + 5 * guiSize;
      layoutNext_y  = y; // this shouldn't be necessary => why?

      color           = COLOR_BLUE;
      colorBackground = COLOR_BLACK;

      //h=sliderHeight;
      h = sliderIndicatorPosY + sliderIndicatorHeight - sliderPosY;
      sliderValue = 10;
    }

    GUI_Slider(char * name)
    {
      init(name);
    };
    
    GUI_Slider(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }


    void show()
    {

      // name
      tft.fillRect(x, namePosY, w, nameHeight, colorBackground);
      //tft.drawRect(x, namePosY, w, nameHeight, color);
      tft.setCursor(x + 2 * guiSize, namePosY + 2 * guiSize);
      tft.setTextColor(COLOR_BLUE);
      tft.setTextSize(guiSize);
      tft.print(sliderName);

      // slider
      tft.fillRect(x, sliderPosY, w, sliderHeight, colorBackground);
      tft.drawRect(x, sliderPosY, w, sliderHeight, COLOR_BLUE);
      tft.drawRect(x + w / 2 - guiSize, sliderPosY + sliderPOintRadius, guiSize * 3, sliderHeight - sliderPOintRadius * 2, COLOR_GREY);
      tft.fillCircle(x + w / 2, sliderPointPosY - sliderPOintRadius, sliderPOintRadius, COLOR_BLUE);
      
      // value
      tft.fillRect(x, sliderIndicatorPosY, w, sliderIndicatorHeight, COLOR_GREY);
      tft.drawRect(x, sliderIndicatorPosY, w, sliderIndicatorHeight, COLOR_BLUE);
      tft.setCursor(x + 2 * guiSize, sliderIndicatorPosY + 2 * guiSize);
      tft.setTextColor(COLOR_BLUE);
      tft.setTextSize(guiSize);
      tft.print(sliderValue);

    }

    int32_t getInt()
    {
      if (isPressed())
      {

        sliderPointPosY = TouchY;
        //if (sliderPointPosY < sliderPosY + nameHeight)sliderPointPosY = sliderPosY + nameHeight;
        //if (sliderPointPosY > sliderIndicatorPosY)sliderPointPosY = sliderIndicatorPosY;
	sliderPointPosY=coerce(sliderPointPosY,sliderPosY + nameHeight,sliderIndicatorPosY);
        sliderValue = map(sliderPointPosY, sliderPosY + nameHeight, sliderIndicatorPosY, 110, -10);
	sliderValue=coerce(sliderValue,0,100);

        show();
      }

      return sliderValue;
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
    uint8_t state = 0;

    uint16_t textPosX, textPosY;


    void init(char * txt)
    {
      buttonName = txt;
      guiSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;

      w = (strlen(buttonName) + 1) * (FONT_WIDTH + 1) * guiSize;

      h = LAYOUT_TILE_HEIGTH * guiSize;


      textPosY      = y + h / 2 - FONT_HEIGTH;
      textPosX      = x + (FONT_WIDTH / 2) * guiSize;

      layoutNext_y += h + guiSize;
      layoutNext_y += 2 * guiSize;

      color           = BUTTON_OFF_COLOR;
      colorBackground = COLOR_BLACK;

    }

    GUI_Button(char * txt)
    {
      init(txt);
    }

    GUI_Button(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void show()
    {

      tft.fillRoundRect(x, y, w, h, 5, color);

      //tft.setCursor(x+2*guiSize, y+ 1*guiSize);
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
              color = BUTOON_ON_COLOR;
              state = 1;
            }
          } break;
        case 1:
          {
            if (!isHit())
            {
              color = BUTTON_OFF_COLOR;
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

    int ElementX, ElementY;
    int ElementW, ElementH;

    int TextPosY;

    void init(char * txt)
    {
      x = layoutNext_x;
      y = layoutNext_y;

      objectName = txt;
      int textOffset = (strlen(txt) + 2) * 5 * guiSize;

      ElementW = LAYOUT_TILE_WIDTH  * guiSize;
      ElementH = h;

      int offset = textOffset + 1;

      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y;

      TextPosY = y + h / 2 + 1;

      layoutNext_y += h + guiSize;

    }

    GUI_labeledObject(char * txt)
    {
      init(txt);
    }

    GUI_labeledObject(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(guiSize);
      tft.setCursor(x, TextPosY);
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

    int ElementX, ElementY;
    int ElementW, ElementH;

    int TextPosY;

    int xx, yy, rr;

    boolean ledState = false;


    void init(char * txt)
    {
      color=COLOR_RED;
      x = layoutNext_x;
      y = layoutNext_y;

      objectName = txt;
      int textOffset = (strlen(txt) + 2) * 5 * guiSize;

      //ElementW = LAYOUT_TILE_WIDTH  * guiSize;
      ElementH = w;
      ElementH = h;

      int offset = textOffset + 1;

      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y;

      TextPosY = y + h / 2 + 1;

      rr = h / 2 - 2;
      xx = ElementX + h / 2;
      yy = ElementY + h / 2;

      layoutNext_y += h + guiSize;
    }

    GUI_Led(char * txt)
    {
      init(txt);
    }

    GUI_Led(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(guiSize);
      tft.setCursor(x, TextPosY);
      tft.print(objectName);
    }

    void show()
    {
      showLabel();
      if(ledState)
      {
	tft.fillCircle(xx, yy, rr, COLOR_GREY);
        tft.fillCircle(xx, yy, rr - 4, color);      
      }else
      {
	tft.fillCircle(xx, yy, rr, COLOR_GREY);
        tft.fillCircle(xx , yy , rr - 4, COLOR_GREY/4);      
      }

    }

    void on()
    {
       ledState=true;	    
       show();
    }

    void off()
    {
       ledState=false;
       show();
    }

    void setLed(boolean offOn)
    {
      if (offOn) on();
      else       off();
    }
    
    void toggle()
    {
      ledState = !ledState;
      setLed(ledState);
    }

};



class GUI_Number: public GUI_Object
{
  public:
    char * objectName;

    int ElementX, ElementY;
    int ElementW, ElementH;

    int TextPosY;

    int number = 0;

    void init(char * txt)
    {
      w = ( FONT_WIDTH + 2 ) * guiSize;
      h = ( FONT_HEIGTH + 2 ) * guiSize;
      x = layoutNext_x;
      y = layoutNext_y;

      objectName = txt;
      int textOffset = (strlen(txt) + 2) * 5 * guiSize;

      //ElementW = LAYOUT_TILE_WIDTH  * guiSize;

      ElementW = (10 + 1 ) * FONT_WIDTH * guiSize; //10 digits
      ElementH = h;

      int offset = textOffset + 1;

      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y ;

      //TextPosY = y + h / 2 + 1;
      TextPosY = y + 1 * guiSize;

      layoutNext_y += h + 3 * guiSize;
    }

    GUI_Number(char * txt)
    {
      init(txt);
    }

    GUI_Number(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(guiSize);
      tft.setCursor(x, TextPosY);
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

      tft.setCursor(ElementX + 2 * guiSize, ElementY + 1 * guiSize);
      tft.setTextColor(color);
      tft.print(number);
      //number frame
      //tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED);
    }

    void print(int num)
    {
      number = num;
      show();
    }

};

class GUI_Text: public GUI_Object
{
  public:
    char * objectName;

    int ElementX, ElementY;
    int ElementW, ElementH;

    int TextPosY;

    char * displayedText;

    void init(char * txt)
    {
      w = ( FONT_WIDTH + 2 ) * guiSize;
      h = ( FONT_HEIGTH + 2 ) * guiSize;
      x = layoutNext_x;
      y = layoutNext_y;

      objectName = txt;
      int textOffset = (strlen(txt) + 2) * 5 * guiSize;

      //ElementW = LAYOUT_TILE_WIDTH  * guiSize;

      ElementW = (10 + 1 ) * FONT_WIDTH * guiSize; //10 digits
      ElementH = h;

      int offset = textOffset + 1;

      w          = ElementW + offset;
      ElementX   = x + offset;
      ElementY   = y ;

      //TextPosY = y + h / 2 + 1;
      TextPosY = y + 1 * guiSize;

      layoutNext_y += h + 3 * guiSize;
    }

    GUI_Text(char * txt)
    {
      init(txt);
      displayedText="";
    }

    GUI_Text(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
      displayedText="";
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(guiSize);
      tft.setCursor(x, TextPosY);
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

      tft.setCursor(ElementX + 2 * guiSize, ElementY + 1 * guiSize);
      tft.setTextColor(color);
      tft.print(displayedText);
      //number frame
      //tft.drawRect(ElementX, ElementY, ElementW, ElementH, COLOR_RED);
    }

    void print(char *txt)
    {
      displayedText=txt;
      show();
    }

};

/************************************************************************************************
 * 
 * GUI_Graph
 * 
 ************************************************************************************************/

#define GRAPH_TEXT_COLOR     COLOR_GREY
#define GRAPH_FRAME_COLOR    COLOR_GREY
#define GRAPH_SIGNAL_COLOR   COLOR_YELLOW

#define SIGNAL_LENGTH 128 // be aware that on the ARDUINO with ATMEGA328 you have only 2K of RAM

class GUI_Graph: public GUI_Object
{
  public:
    char * graphName;
    uint8_t state = 0;

    uint16_t textPosX, textPosY;

    uint16_t HORIZONTAL_RESOLUTION;
    uint16_t VERTICAL_RESOLUTION;
    uint16_t POSITION_OFFSET_Y;

    //uint16_t oldSignal[SIGNAL_LENGTH];
    uint16_t *oldSignal;//[SIGNAL_LENGTH];
    bool firstCallFlag;

    //uint16_t signalBuffer[SIGNAL_LENGTH];

    int16_t rangeMin;
    int16_t rangeMax;

    void setRange(int16_t lowerLimit, int16_t upperLimit )
    {
      rangeMin = lowerLimit;
      rangeMax = upperLimit;
    }

    void init(char * txt, uint16_t width, uint16_t height)
    {
      firstCallFlag = true;

      setRange(0, 255);
      graphName = txt;
      guiSize = 2;
      x = layoutNext_x;
      y = layoutNext_y;

      //w = (strlen(graphName) + 1) * (FONT_WIDTH + 1) * guiSize;

      //h = LAYOUT_TILE_HEIGTH * guiSize;

      //w = SIGNAL_LENGTH;
      //h = 120;
      w = width;
      h = height;

      HORIZONTAL_RESOLUTION = w;
      POSITION_OFFSET_Y = 20;
      VERTICAL_RESOLUTION = h - POSITION_OFFSET_Y;

      //textPosY      = y + h / 2 - FONT_HEIGTH;
      //textPosX      = x + (FONT_WIDTH / 2) * guiSize;

      textPosY      = y;
      textPosX      = x;

      layoutNext_y += h + guiSize;
      //layoutNext_x += w + 2 * guiSize;

      color           = COLOR_GREEN;
      colorBackground = COLOR_BLACK;

    }

    GUI_Graph(char * txt)
    {
      uint16_t width = 128;
      uint16_t height = 120;
      init(txt, width, height);
    }

    GUI_Graph(char * txt, uint16_t width, uint16_t height)
    {
      init(txt, width, height);
    }

    GUI_Graph(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      uint16_t width = 128;
      uint16_t height = 120;
      init(txt, width, height);
    }

    GUI_Graph(uint16_t posX, uint16_t posY, char * txt, uint16_t width, uint16_t height)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt, width, height);
    }

    void show()
    {

      // draw frame
      tft.drawRect(x, y + POSITION_OFFSET_Y, HORIZONTAL_RESOLUTION + 2, VERTICAL_RESOLUTION + 2, GRAPH_FRAME_COLOR);
      //tft.fillRect(x, y + POSITION_OFFSET_Y, HORIZONTAL_RESOLUTION + 2, VERTICAL_RESOLUTION + 2, GRAPH_FRAME_COLOR);

      // draw label
      //tft.setCursor(x+2*guiSize, y+ 1*guiSize);
      tft.setTextSize(guiSize / 2);
      tft.setCursor(textPosX, textPosY + FONT_HEIGTH);

      tft.setTextColor( GRAPH_TEXT_COLOR );
      tft.print(graphName);
    }

    void show(int16_t *signalBuffer, uint16_t signalLength)
    {
      int n;

      int oldx;
      int oldy;
      int oldSig;
      int xx, yy;

      show();

      // reserve buffer for old signal on first call.
      // later change of signal length is forbidden
      if (firstCallFlag)
      {
        oldSignal = (uint16_t*)malloc(signalLength * 2);
        for(n=0;n<signalLength;n++)oldSignal[n]=0;
        firstCallFlag = false;
      }

      for (n = 0; n < signalLength; n++)
      {
        xx = n + x + 1;
        int sig = coerce(signalBuffer[n], rangeMin, rangeMax);

        yy = map(sig, rangeMin, rangeMax, y + VERTICAL_RESOLUTION + POSITION_OFFSET_Y, y + POSITION_OFFSET_Y);

        if (n > 0)
        {
          // delete old line element
          tft.drawLine(oldx , oldSig, xx, oldSignal[n], COLOR_BLACK );

          // draw new line element
          if (n < signalLength - 1) // don't draw last element because it would generate artifacts
          {
            tft.drawLine(oldx,    oldy, xx,            yy, GRAPH_SIGNAL_COLOR );
            //tft.drawLine(oldx,    oldy, xx,            yy, COLOR_GREEN );
          }
        }
        oldx = xx;
        oldy = yy;
        oldSig = oldSignal[n];
        oldSignal[n] = yy;
      }
    }
};
/************************************************************************************************
 * 
 * GUI_Menue
 * 
 ************************************************************************************************/
#define MENUE_SELECTED_COLOR COLOR_RED
#define MENUE_LABEL_COLOR    COLOR_GREEN
#define MENUE_TEXT_COLOR     COLOR_WHITE
#define MENUE_FRAME_COLOR    COLOR_GREY/2

class GUI_Menue : public GUI_Object
{
  public:
    char * objectName;

    int ElementX, ElementY;
    int ElementW, ElementH;

    int textPosY;
    int textPosX;

    int xx, yy;

    char **menue;
    uint8_t numberOfEntries;

    int8_t index;
    int8_t numberOfEntriesDisplayed;

    void set(char **menueStringArray, uint8_t numberOfEntries_)
    {
      menue = menueStringArray;
      numberOfEntries = numberOfEntries_;
    }

    void init(char * txt)
    {
      numberOfEntriesDisplayed = 3;
      index = 0;
      color = COLOR_RED;
      x = layoutNext_x;
      y = layoutNext_y;

      objectName = txt;
      int textOffset = (strlen(txt) + 2) * 5 * guiSize;

      //ElementW = LAYOUT_TILE_WIDTH  * guiSize;
      ElementH = w;
      ElementH = h;

      int offset = textOffset + 1;

      w          = 80;
      h          = 100;
      ElementX   = x + offset;
      ElementY   = y;

      textPosX   = x;
      textPosY   = y;// + guiSize;


      //rr = h / 2 - 2;
      //xx = ElementX + h / 2;
      //yy = ElementY + h / 2;

      //layoutNext_y += h + guiSize;//FONT_HEIGTH * 2
      layoutNext_y += h + FONT_HEIGTH * 4;
    }

    GUI_Menue(char * txt)
    {
      init(txt);
    }

    GUI_Menue(uint16_t posX, uint16_t posY, char * txt)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt);
    }

    void showLabel()
    {
      tft.setTextColor(COLOR_GREEN);
      tft.setTextSize(guiSize);
      tft.setCursor(x, textPosY);
      tft.print(objectName);
    }

    void show()
    {
      int8_t idx;

      // draw frame
      int pos = textPosY;//+ FONT_HEIGTH;

      uint8_t font_height;
      font_height = FONT_HEIGTH * 2;

      tft.fillRect(x, pos + font_height * 2, w, h, MENUE_FRAME_COLOR);

      pos += font_height;
      //tft.fillRect(x, y + POSITION_OFFSET_Y, HORIZONTAL_RESOLUTION + 2, VERTICAL_RESOLUTION + 2, GRAPH_FRAME_COLOR);

      // draw label
      //tft.setCursor(x+2*guiSize, y+ 1*guiSize);
      tft.setTextSize(guiSize );

      tft.setCursor(textPosX, pos );
      tft.setTextColor( MENUE_LABEL_COLOR );
      tft.print(objectName);
      tft.setTextColor( MENUE_TEXT_COLOR );
      idx = index;

      pos += font_height;

      idx--;
      if (idx < 0)idx = numberOfEntries - 1;

      for (int n = 0; n < numberOfEntriesDisplayed; n++)
      {
        pos += font_height;
        tft.setCursor(textPosX, pos );
        if (n == 1) tft.setTextColor( COLOR_YELLOW, MENUE_SELECTED_COLOR );
        else        tft.setTextColor( MENUE_TEXT_COLOR );

        tft.print(menue[idx]);
        idx++;
        if (idx > numberOfEntries - 1)
        {
          pos += font_height;
          tft.setCursor(textPosX, pos );
          tft.setTextColor( MENUE_TEXT_COLOR );
          tft.print("-----");
          idx = 0;
        }
      }

    }

    void up()
    {
      index++;
      if (index >= numberOfEntries)index = 0;
      show();
    }

    void down()
    {
      index--;
      if (index < 0) index = numberOfEntries;
      show();
    }

    int8_t getIndex()
    {
      return index;
    }

};
#endif

/* GuiPittix simple graphical user interface elemetns

   © ChrisMicro 2017-2019.

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

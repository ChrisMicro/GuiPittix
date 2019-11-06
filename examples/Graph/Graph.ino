/*
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   Graph example

   2019, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_STM32F746_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm
#define TFT_Adapter_ILI9341_F407_Discovery

#include "Gui.h"

//#define BUTTON_OFF_COLOR   COLOR_GREY/3*2
//#define BUTOON_ON_COLOR    COLOR_WHITE
//#define BUTTON_TEXT_COLOR  COLOR_BLUE
#define GRAPH_TEXT_COLOR     COLOR_GREY
#define GRAPH_FRAME_COLOR    COLOR_GREY/3
#define GRAPH_SIGNAL_COLOR   COLOR_YELLOW

#define SIGNAL_LENGTH 128

class GUI_Graph: public GUI_Object
{
  public:

    char * graphName;
    uint8_t state = 0;

    uint16_t textPosX, textPosY;

    uint16_t HORIZONTAL_RESOLUTION;
    uint16_t VERTICAL_RESOLUTION;
    uint16_t POSITION_OFFSET_Y;

    uint16_t oldSignal[SIGNAL_LENGTH];
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
      layoutNext_y += 2 * guiSize;

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

    GUI_Graph(uint16_t posX, uint16_t posY, char * txt,uint16_t width, uint16_t height)
    {
      layoutNext_x = posX;
      layoutNext_y = posY;
      init(txt, width, height);
    }
    
    void show()
    {
      // draw frame
      tft.drawRect(x, y + POSITION_OFFSET_Y, HORIZONTAL_RESOLUTION + 2, VERTICAL_RESOLUTION + 2, GRAPH_FRAME_COLOR);

      // draw label
      //tft.setCursor(x+2*guiSize, y+ 1*guiSize);
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
      uint16_t len;

      len = signalLength;
      if (signalLength > SIGNAL_LENGTH)len = SIGNAL_LENGTH;

      for (n = 0; n < len; n++)
      {
        xx = n + x + 1;
        yy = map(signalBuffer[n], rangeMin, rangeMax, y + VERTICAL_RESOLUTION + POSITION_OFFSET_Y, y + POSITION_OFFSET_Y);

        if (n > 0)
        {
          // delete old line element
          tft.drawLine(oldx , oldSig, xx, oldSignal[n], COLOR_BLACK );

          // draw new line element
          if (n < len - 1) // don't draw last element because it would generate artifacts
          {
            tft.drawLine(oldx,    oldy, xx,            yy, GRAPH_SIGNAL_COLOR );
          }
        }
        oldx = xx;
        oldy = yy;
        oldSig = oldSignal[n];
        oldSignal[n] = yy;
      }
    }
};

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");
GUI_Graph graph1(160,20,"analog0",120,80);// xpos, ypos, name, width, heigth


void setup()
{
  gui.begin();
  graph1.show();
  graph1.setRange(0, 100);
}

#define SIGNAL_LENGTH 100

void loop(void)
{
  led1.on();
  delay(100);
  led1.off();
  delay(100);

  int16_t buffer[SIGNAL_LENGTH];
  for (int n = 0; n < SIGNAL_LENGTH; n++) buffer[n] = random(0, 100);
  graph1.show(buffer, SIGNAL_LENGTH);

  // we can blink easier:
  led2.toggle();
}

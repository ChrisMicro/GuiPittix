/*
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   Button Example

   2017, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_SPFD5408_UNO
#define TFT_Adapter_STM32F746_Discovery
#include "TouchScreen_F7_Discovery.h" // TOUCH

TouchScreen ts;

#include "Gui.h"

GUI_Button button1 ( 50,100,"  up");
GUI_Button button2 (        "down");

GUI_Number number  ( 50, 50,"counter");

void setup()
{
  gui.begin();

  button1.show();
  button2.show();
  number.show();
}

int Counter = 0;

void loop(void)
{
  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  if (button1.wasPressed())  Counter++;
  if (button2.wasPressed())  Counter--;

  number.print(Counter);
  
  delay(50);
}












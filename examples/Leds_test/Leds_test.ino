/* 
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   LED example

   2017, ChrisMicro
*/

// choose your hardware:
#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_STM32F746_Discovery

#include "Gui.h"

GUI_Led   Led1("up  ");
GUI_Led   Led2("down");

void setup()
{
  gui.begin();
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












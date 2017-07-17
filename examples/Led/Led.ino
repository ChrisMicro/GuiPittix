/* 
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   LED example

   2017, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_STM32F746_Discovery
#define TFT_TEK // TEK4010 emulation to Teraterm

#include "Gui.h"

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");

void setup()
{
  gui.begin();
}

void loop(void)
{
  led1.on();
  delay(1000);
  led1.off();
  delay(1000);

  // we can blink easier:
  led2.toggle();
}











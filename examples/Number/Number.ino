/* 
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   Number example

   2017, ChrisMicro
*/

// choose your hardware:
#define TFT_Adapter_CYD_V1_2
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_STM32F746_Discovery
//#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm

#include "Gui.h"

GUI_Led    led    ( 0,0,   " clock");
GUI_Number number ( 120,10," count");
GUI_Number number2(        "    x3");
GUI_Number number3(        "square");

void setup()
{
  gui.begin();
  led.setColor(COLOR_RED);
  number.show();
}

int Counter = 1;

void loop(void)
{  
  led.on();
  delay(100);
  led.off();
  delay(100);

  number.print  ( Counter );
  number2.print ( Counter*3 );
  number3.print ( Counter*Counter );
  
  Counter++;

}












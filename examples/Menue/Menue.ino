/*
   GuiPittix simple graphical user interface elemetns

   scroll menue example

   2019, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_STM32F746_Discovery
#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm

#include "Gui.h"

#define USER_BUTTON PA0

#define SIGNAL_LENGTH 128

GUI_Menue  menue (       "menue");
GUI_Number number(       "selected");
GUI_Led    led1  (160,40,"set   ");
GUI_Led    led2  (       "toggle");

const int NumberOfMenueEntries = 5;
char *Menue[] = {"point0", "point1", "point2", "point3", "point4" };

void setup()
{
  Serial.begin(115200);
  gui.begin();
  menue.set(Menue, NumberOfMenueEntries);
  menue.show();
}

void loop(void)
{
  if  ( digitalRead( USER_BUTTON ) )  menue.up();
  
  number.print(menue.getIndex());
  
  led1.on();
  delay(100);
  led1.off();
  delay(100);

  led2.toggle();

}

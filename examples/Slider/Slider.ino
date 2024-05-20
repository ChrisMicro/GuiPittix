/*
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   Slider Example

   2017, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_CYD_V1_2
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
#define TFT_Adapter_STM32F746_Discovery
//#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm
#include "TouchScreen_F7_Discovery.h" // TOUCH

TouchScreen ts;

#include "Gui.h"

GUI_Slider slider1 (  10,   0, "s1"  );
GUI_Slider slider2 (           "s2"  ); // use Layoutmanger, slider is auto placed to the right
GUI_Number number  ( 150, 100, "s1 x s2 " );

void setup()
{
  gui.begin();
  slider1.show();
  slider2.show();
  number.show();
}

int Counter = 0;

void loop(void)
{
  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  int value1 = slider1.getInt();
  int value2 = slider2.getInt();
  
  number.print(value1*value2);
  
  delay(50);
}












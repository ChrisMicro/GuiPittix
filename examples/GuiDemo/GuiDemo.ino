/*
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   GUI Demo

   2017, ChrisMicro
*/

// choose your hardware:
//#define TFT_Adapter_CYD_V1_2
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
#define TFT_Adapter_STM32F746_Discovery
//#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm
#define TFT_Adapter_STM32F746_Discovery
#include "TouchScreen_F7_Discovery.h" // TOUCH

TouchScreen ts;

#include "Gui.h"

//GUI_Slider slider1 (           "-"  );
GUI_Slider slider2 ( 20, 20,          "speed"  ); 

GUI_Button button(350, 200, "reset");
GUI_Number number1(160, 30, "count");
GUI_Led led1("   D1");
GUI_Led led2("   D2");
GUI_Led led3("   D3");
GUI_Led led4("   D4");

GUI_Led led5("clock");

void setup()
{
  gui.begin();
  slider2.show();
  button.show();

  number1.show();
  led1.show();
  led2.show();
  led3.show();
  led4.show();
  led5.setColor(COLOR_GREEN);
}

int Counter = 0;

void loop(void)
{

  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  int value2 = slider2.getInt();

  led1.setLed((Counter & 1) != 0);
  led2.setLed((Counter & 2) != 0);
  led3.setLed((Counter & 4) != 0);
  led4.setLed((Counter & 8) != 0);

  led5.toggle();

  number1.print(Counter++);

  if (button.wasPressed()) Counter = 0;
  delay((100 - value2) * 3);
}












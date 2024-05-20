/*
   GuiPittix simple graphical user interface elemetns

   signal graph example

   2019, ChrisMicro
*/

// choose your hardware:
#define TFT_Adapter_CYD_V1_2
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_STM32F746_Discovery
//#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm

#include "Gui.h"

#define SIGNAL_LENGTH 128

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");
GUI_Graph graph1(160, 20, "graph1: noise", SIGNAL_LENGTH, 80); // xpos, ypos, name, width, heigth
GUI_Graph graph2(         "graph2: sine",  SIGNAL_LENGTH, 80); // name, width, heigth

void setup()
{
  gui.begin();
  graph1.show();// show immediatelly
  graph1.setRange(0, 100);
  graph2.setRange(-100, 100);
}

int Counter = 0;

int16_t buffer[SIGNAL_LENGTH];

void loop(void)
{
  led1.on();

  for (int n = 0; n < SIGNAL_LENGTH; n++) buffer[n] = random(0, 100);
  graph1.show(buffer, SIGNAL_LENGTH);

  for (int n = 0; n < SIGNAL_LENGTH; n++) buffer[n] = 100 * sin(2 * PI * n / SIGNAL_LENGTH + Counter);
  graph2.show(buffer, SIGNAL_LENGTH);

  led1.off();

  led2.toggle();

  Counter++;

  delay(100);
}

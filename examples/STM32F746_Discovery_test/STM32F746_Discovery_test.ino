/* 
   GuiPittix simple graphical user interface elemetns

   minimalistic Graphical user interface

   LED example
   
   2017, ChrisMicro
*/

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













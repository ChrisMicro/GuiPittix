/*
   GuiPittix simple graphical user interface elemetns

   CYD example

   2024, ChrisMicro
*/

// choose your hardware:
#define TFT_Adapter_CYD_V1_2
//#define TFT_Adapter_SPFD5408_UNO
//#define TFT_Adapter_ILI9341_BluePill
//#define TFT_Adapter_STM32F746_Discovery
//#define TFT_Adapter_ILI9341_F407_Discovery
//#define TFT_TEK // TEK4010 emulation to Teraterm
//#define TFT_TEK // TEK4010 emulation to Teraterm

#include "Gui.h"

#include <XPT2046_Touchscreen.h>
// A library for interfacing with the touch screen
//
// Can be installed from the library manager (Search for "XPT2046")
// https://github.com/PaulStoffregen/XPT2046_Touchscreen
// The CYD touch uses some non default
// SPI pins

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);

void printTouchToSerial(TS_Point p) {
  Serial.print("Pressure = ");
  Serial.print(p.z);
  Serial.print(", x = ");
  Serial.print(p.x);
  Serial.print(", y = ");
  Serial.print(p.y);
  Serial.println();
}

GUI_Led       led1 (150, 10, "led1");
GUI_Led       led2 (          "led2");

GUI_Slider slider1 (  10,   0, "s1"  );
GUI_Slider slider2 (           "s2"  ); // use Layoutmanger, slider is auto placed to the right
GUI_Number number  ( 150, 100, "s1 x s2 " );

void setup()
{
  Serial.begin(115200);

  gui.begin();
  slider1.show();
  slider2.show();
  number.show();

  // Start the SPI for the touch screen and init the TS library
  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(mySpi);
  ts.setRotation(1);
}

int Counter = 0;
// display 320x240
void loop(void)
{
  led1.toggle();
  led2.toggle();

  if (ts.tirqTouched() && ts.touched())
  {
    TS_Point p = ts.getPoint();
    // limit points have to be callibrated individually for the display
    int x = map(p.x, 232, 3718, 0, 320);
    int y = map(p.y, 275, 3835, 0, 240);

    gui.setTouch(x, y, p.z);

    int value1 = slider1.getInt();
    int value2 = slider2.getInt();

    number.print(value1 * value2);


    printTouchToSerial(p);

  }
  delay(50);
}

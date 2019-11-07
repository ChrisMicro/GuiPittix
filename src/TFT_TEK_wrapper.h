/*
   Adafruit_GFX to Tek Interface

   https://en.wikipedia.org/wiki/Tektronix_4010
   http://www.stm32duino.com/viewtopic.php?f=18&t=2336#p31430
   
   Inspired py Pito Pukao Hats Cleaning Services Ltd.
   
   2017 July ChrisMicro

*/
#ifndef _TFT_Adapter_
#define _TFT_Adapter_

#include "Arduino.h"

#include "Adafruit_GFX.h"

#define COLOR_BLACK       0x0000      /*   0,   0,   0 */
#define COLOR_NAVY        0x000F      /*   0,   0, 128 */
#define COLOR_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define COLOR_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define COLOR_MAROON      0x7800      /* 128,   0,   0 */
#define COLOR_PURPLE      0x780F      /* 128,   0, 128 */
#define COLOR_OLIVE       0x7BE0      /* 128, 128,   0 */
#define COLOR_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define COLOR_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define COLOR_GREY        COLOR_LIGHTGREY
#define COLOR_BLUE        0x001F      /*   0,   0, 255 */
#define COLOR_GREEN       0x07E0      /*   0, 255,   0 */
#define COLOR_CYAN        0x07FF      /*   0, 255, 255 */
#define COLOR_RED         0xF800      /* 255,   0,   0 */
#define COLOR_MAGENTA     0xF81F      /* 255,   0, 255 */
#define COLOR_YELLOW      0xFFE0      /* 255, 255,   0 */
#define COLOR_WHITE       0xFFFF      /* 255, 255, 255 */
#define COLOR_ORANGE      0xFD20      /* 255, 165,   0 */
#define COLOR_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define COLOR_PINK        0xF81F

#define TEK_HEIGHT 768

class TFT_Adapter : public Adafruit_GFX {
  private:
    uint16_t oldRGB565Color;
    // ********************************************************
    // TEK4010/4014 basic commands library
    // For details consult the TEK4010/4014 manual
    // Pito 7/2017 for stm32duino
    // ********************************************************

    // Clear Tek screen
    void Tekcls() {
      Serial.write(0x1B);
      Serial.write(0x0c);
      //Serial.write(0x0d);Serial.write(0x0a);
    }

    // Select a color
    // [0 = Black, 1 = Red, 2 = Green, 3 = Yellow, 4 = Blue, 5 = Magenta, 6 = Cyan, 7 = White]
    void Tekcolor(uint8_t color) {
      Serial.write(0x1B);
      Serial.write(0x5b);
      Serial.write(0x33);
      Serial.write(0x30 + color);
      Serial.write(0x6d);
    }

    // Switch to graphical mode with a line style (0-5)
    void Tekgraph(uint8_t style) {
      Serial.write(0x1D);
      Serial.write(0x1B);
      Serial.write(style | 0x60);
    }

    // Select a font size (0-5) for printing strings
    // The actual font has to be set in Emulator
    void Tekfont(uint8_t fontsize) {
      Serial.write(0x1B);
      Serial.write(0x38 + fontsize);
    }

    // Normal style lines (0-5)
    void Tekstyle(uint8_t style) {
      Serial.write(0x1B);
      Serial.write(0x60 + style);
    }

    // Bold style lines (??)
    void Tekstyleb(uint8_t style) {
      Serial.write(0x1B);
      Serial.write(0x68 + style);
    }

    // Switch to alphanumeric mode
    void Tekalpha() {
      Serial.write(0x1f);
    }

    // Draw a point as a small cross (??)
    void Tekpoint(uint16_t x, uint16_t y) {
      Serial.write(0x1C);  // FS
      Serial.write(0x20 + ((y >> 5) & 0x1F));
      Serial.write(0x60 + ((y) & 0x1F));
      Serial.write(0x20 + ((x >> 5) & 0x1F));
      Serial.write(0x40 + ((x) & 0x1F));
    }

    // Draw a single dot
    void Tekdot(uint16_t x, uint16_t y) {
      Serial.write(0x1D);  // GS
      Serial.write(0x20 + ((y >> 5) & 0x1F));
      Serial.write(0x60 + ((y) & 0x1F));
      Serial.write(0x20 + ((x >> 5) & 0x1F));
      Serial.write(0x40 + ((x) & 0x1F));
      Serial.write(0x40 + ((x) & 0x1F));
    }

    // Draw a line from (x1, y1) to (x2, y2)
    void Tekline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
      Serial.write(0x1D);  // GS
      Serial.write(0x20 + ((y1 >> 5) & 0x1F));
      Serial.write(0x60 + ((y1) & 0x1F));
      Serial.write(0x20 + ((x1 >> 5) & 0x1F));
      Serial.write(0x40 + ((x1) & 0x1F));
      Serial.write(0x20 + ((y2 >> 5) & 0x1F));
      Serial.write(0x60 + ((y2) & 0x1F));
      Serial.write(0x20 + ((x2 >> 5) & 0x1F));
      Serial.write(0x40 + ((x2) & 0x1F));
    }

    // Continue with drawing a line to (x1, y1)
    void Tekplot(uint16_t x1, uint16_t y1) {
      Serial.write(0x20 + ((y1 >> 5) & 0x1F));
      Serial.write(0x60 + ((y1) & 0x1F));
      Serial.write(0x20 + ((x1 >> 5) & 0x1F));
      Serial.write(0x40 + ((x1) & 0x1F));
    }

    // Locate a point where to print a string
    void Teklocate(uint16_t x1, uint16_t y1) {
      Serial.write(0x1D);  // GS
      Serial.write(0x20 + ((y1 >> 5) & 0x1F));
      Serial.write(0x60 + ((y1) & 0x1F));
      Serial.write(0x20 + ((x1 >> 5) & 0x1F));
      Serial.write(0x40 + ((x1) & 0x1F));
      Tekalpha();
    }

    // Draw a box with left bottom corner at (bx, by) and top right corner at (tx, ty)
    void Tekbox(uint16_t bx, uint16_t by, uint16_t tx, uint16_t ty) {
      Tekline(bx, by, tx, by);
      Tekplot(tx, ty);
      Tekplot(bx, ty);
      Tekplot(bx, by);
    }

  public:
    TFT_Adapter(): Adafruit_GFX((int16_t) 480, (int16_t) 270)
    {

    }

    void init()
    {

    };

    void begin()
    {
      Serial.begin(115200);

    };

    uint32_t RGB565TORGB8888(int16_t RGB565)
    {
      int color = RGB565;
      uint8_t r = ((color >> 11) & 0x1F) << 3;
      uint8_t g = ((color >> 5) & 0x3F) << 2;
      uint8_t b = (color & 0x1F) << 3;
      uint32_t RGB8888 = 0XFF000000 | r << 16 | g << 8 | b;

      return RGB8888;
    }

    // ********************* Adruit Wrapper ******************************
    // 17.7.2017 ChrisMicro
    // ******************************************************************
    // [0 = White, 1 = Red, 2 = Green, 3 = Yellow, 4 = Blue, 5 = Magenta, 6 = Cyan, 7 = Böack]
    void setTekColor(uint16_t color)
    {
      if ( oldRGB565Color != color )
      {
        uint8_t tekColor = 0;
        if ( color == COLOR_BLACK ) tekColor = 7;
        if ( color == COLOR_RED ) tekColor = 1;
        if ( color == COLOR_GREEN ) tekColor = 2;
        if ( color == COLOR_YELLOW ) tekColor = 3;
        if ( color == COLOR_BLUE ) tekColor = 4;
        if ( color == COLOR_MAGENTA ) tekColor = 5;
        if ( color == COLOR_CYAN ) tekColor = 6;
        if ( color == COLOR_WHITE ) tekColor = 0;
        Tekcolor(tekColor);
        oldRGB565Color = color;
      }

    }
    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
      setTekColor(color);
      y = TEK_HEIGHT - y;
      Tekdot(x, y);
    };

    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
    {
      setTekColor(color);
      y = TEK_HEIGHT - y;
      Tekline(x, y, x, y - h);
    };

    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
    {
      setTekColor(color);
      y = TEK_HEIGHT - y;
      Tekline(x, y, x + w, y);
    };
    /*
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
        {


        };
    */
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
    {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
    }

};
#endif // TFT_Adapter

/* 
   © ChrisMicro 2017.
   This file is part of GuiPittix.
   ArduinoOnPc is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   GuiPittix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public License
   along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.

   If you use simple_GUI_elements in public project you can inform me about this by e-mail,
   of course if you want it.

   web-site: https://github.com/ChrisMicro/GuiPittix
*/


/*
 * GuiPittix TFT Adapter
 * 
 * Chnage this file depending on your hardware configuration
 * 
 * Hardware:
 *  TFT: SDFP5408 Arduino Shield with parallel interface
 *  http://www.ebay.de/itm/2-4-TFT-LCD-Display-Shield-Touch-Panel-ILI9341-240X320-for-Arduino-UNO-MEGA-/382052804437
 *  Library https://github.com/JoaoLopesF/SPFD5408
 *  MCU: Arduino Uno
 *
 * 2017, ChrisMicro
 * 
 */
#ifndef _TFT_ADAPTER_
#define _TFT_ADAPTER_

#include <stdint.h>
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

class TFT_Adapter : public Adafruit_TFTLCD 
{
  public:
    TFT_Adapter():Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4){};
    void begin()
    {
      Adafruit_TFTLCD::begin((uint16_t)0x9341); // SDFP5408
      Adafruit_TFTLCD::setRotation(3); 
    };

};

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

#endif // _TFT_ADAPTER_ 

/* GuiPittix simple graphical user interface elemetns
 *   
 * © ChrisMicro 2017.
 *
 * This file is part of GuiPittix.
 *
 * GuiPittix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GuiPittix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.
 *
 * If you use simple_GUI_elements in public project you can inform me about this by e-mail,
 * of course if you want it.
 *
 * web-site: https://github.com/ChrisMicro/GuiPittix
 */




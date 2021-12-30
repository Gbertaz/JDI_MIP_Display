// MIT License
//
// Copyright(c) 2021 Giovanni Bertazzoni <nottheworstdev@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef JDI_MIP_Display_h
#define JDI_MIP_Display_h

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Display_cfg.h>

//#define DIFF_LINE_UPDATE

#define COLOR_BLACK             0x00
#define COLOR_BLUE              0x02
#define COLOR_GREEN             0x04
#define COLOR_CYAN              0x06
#define COLOR_RED               0x08
#define COLOR_MAGENTA           0x0a
#define COLOR_YELLOW            0x0c
#define COLOR_WHITE             0x0e

#define CMD_NO_UPDATE           0x00
#define CMD_BLINKING_BLACK      0x10
#define CMD_BLINKING_INVERSION  0x14
#define CMD_BLINKING_WHITE      0x18
#define CMD_ALL_CLEAR           0x20
#define CMD_VCOM                0x40
#define CMD_UPDATE              0x90

class JDI_MIP_Display : public Adafruit_GFX{
    public:
        JDI_MIP_Display();
        void begin();
        void refresh();
        void displayOn();
        void displayOff();
        void clearScreen();
        void frontlightOn();
        void frontlightOff();
        void setBackgroundColor(uint16_t color);

    private:
        uint8_t _scs;       //Chip Select Signal
        uint8_t _disp;      //Display ON/OFF Switching Signal
        uint8_t _frontlight;
        uint16_t _background;
        char _cmdBuffer[DISPLAY_WIDTH / 2];
        char _backBuffer[(DISPLAY_WIDTH / 2) * DISPLAY_HEIGHT];

#ifdef DIFF_LINE_UPDATE
        char _dispBuffer[(DISPLAY_WIDTH / 2) * DISPLAY_HEIGHT];
#endif

        void sendLineCommand(char* line_cmd, int line);
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        bool compareBuffersLine(int lineIndex);
};
#endif
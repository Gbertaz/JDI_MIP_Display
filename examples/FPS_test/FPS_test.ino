//======================================================================
//======================================================================
//  Program: FPS_test.ino
//
//  Description: The purpose of the sketch is to test the correct
//                communication with a Memory In Pixel Display
//                produced by Japan Display Inc. by filling the
//                screen with some colored moving rectangles and
//                showing the FPS.
//                This test doesn't take advantage of the diff lines
//                update because the entire buffer changes at every
//                display refresh.
//
//                I have tested the sketch only with the LPM027M128B
//                but it should work with all the JDI MIP Displays
//                with the SPI interface such as LPM044M141A
//                LPM013M126A and so on.
//                https://github.com/Gbertaz/JDI_MIP_Display
//
//
//  Wiring:     The Displays have a 10 pins FPC connector with the following I/O pins:
//                1  SCLK:     SPI Serial Clock Signal                                                  =>    connect to MCU SPI Clock              =>    Teensy 4.1 pin 13
//                2  SI/MOSI   SPI Serial Data Input Signal also known as MOSI (Master Out Slave In)    =>    connect to MCU SPI MOSI               =>    Teensy 4.1 pin 11
//                3  SCS       SPI Chip Select Signal                                                   =>    connect to MCU SPI Chip select pin    =>    Teensy 4.1 pin 10
//                4  EXTCOMIN  COM Inversion Signal Input                                               =>    not connected
//                5  DISP      Display ON/OFF Switching Signal                                          =>    connect to any digital pin            =>    Teensy 4.1 pin 22
//                6  VDDA      Power Supply for Analog                                                  =>    3.3v
//                7  VDD       Power Supply for Logic                                                   =>    3.3v
//                8  EXTMODE   COM Inversion Mode Select Terminal                                       =>    ground
//                9  VSS       Logic Ground                                                             =>    ground
//                10 VSSA      Analog Ground                                                            =>    ground
//
//              If you are using my breakout board there is an additional pin to control the frontlight =>    connect to any digital pin            =>    Teensy 4.1 pin 23
//              More info about the breakout board: https://github.com/Gbertaz/JDI_MIP_Display#breakout-board
//
//
//  Prerequisites:
//     1) Open Display_cfg.h 
//     2) Configure the required pins according to your wiring scheme: PIN_SCS, PIN_DISP, PIN_FRONTLIGHT
//     3) Set the width and height in pixel according to your display model: DISPLAY_WIDTH, DISPLAY_HEIGHT
//
//
//  License:
//
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
//
//======================================================================
//======================================================================

#include <JDI_MIP_Display.h>

#define NUMBER_COLORS 8

const uint16_t colors[NUMBER_COLORS] = {COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE};

JDI_MIP_Display jdi_display;

int rectHeight = jdi_display.height() / NUMBER_COLORS;
int rectWidth = jdi_display.width() / 2;
int startColor = 0;
int currentColor = 0;

int fps = 0;
unsigned int frames = 0;
unsigned long startMillis = 0;

void setup() {
  jdi_display.begin();
  delay(50);
  jdi_display.displayOn();
  jdi_display.frontlightOn();         //Optional depending on the display model
  jdi_display.clearScreen();          //Clear the screen
  jdi_display.refresh();              //Actually updates the display
  startMillis = millis();
}

void loop() {
  scrollingColors();
  jdi_display.fillCircle(jdi_display.width() / 2, jdi_display.height() / 2, 60, COLOR_BLUE);

  int xPos = (jdi_display.width() / 2) - 25;
  int yPos = (jdi_display.height() / 2) - 45;

  jdi_display.setTextColor(COLOR_BLACK, COLOR_WHITE);
  jdi_display.setTextSize(3);
  jdi_display.setCursor(xPos, yPos);
  jdi_display.print("fps");
  
  if(fps >= 10) xPos -= 20;
  jdi_display.setTextColor(COLOR_WHITE);
  jdi_display.setTextSize(8);
  jdi_display.setCursor(xPos + 5, yPos + 30);
  jdi_display.print(fps);
  jdi_display.refresh();      //Actually updates the display
  
  fps = frames / ((millis() - startMillis) / 1000);
  frames++;
}


void scrollingColors(){
  
  int y = 0;
  
  currentColor = startColor;
  
  for(int i = 0; i < NUMBER_COLORS; i++){
    jdi_display.fillRect(0, y, rectWidth, rectHeight, colors[currentColor]);
    y += rectHeight;
    currentColor++;
    if(currentColor > NUMBER_COLORS - 1) currentColor %= NUMBER_COLORS;
  }

  currentColor = startColor;
  y = jdi_display.height() - rectHeight;
  for(int i = 0; i < NUMBER_COLORS; i++){
    jdi_display.fillRect(rectWidth, y, rectWidth, rectHeight, colors[currentColor]);
    y -= rectHeight;
    currentColor++;
    if(currentColor > NUMBER_COLORS - 1) currentColor %= NUMBER_COLORS;
  }
  
  if(startColor < NUMBER_COLORS - 1) startColor++;
  else startColor = 0;
}

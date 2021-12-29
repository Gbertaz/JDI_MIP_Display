//======================================================================
//======================================================================
//  Program: EfficientUpdate_test.ino
//
//  Description: This sketch was made to create a test case to improve
//                the screen refresh rate by updating only the lines 
//                that change between two screen refresh.
//                Splits the screen into small squares, for each 
//                screen refresh fills one of them with a random
//                color. Try to change the SQUARE_SIZE and compare
//                the results between full screen update by commenting
//                DIFF_LINE_UPDATE in JDI_MIP_Display.h
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

#define NUMBER_COLORS 6
#define SQUARE_SIZE 20

const uint16_t colors[NUMBER_COLORS] = { COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW };

JDI_MIP_Display jdi_display;

int columns = jdi_display.width() / SQUARE_SIZE;
int rows = jdi_display.height() / SQUARE_SIZE;

int fps = 0;
unsigned int frames = 0;
unsigned long lastFpsMillis = 0;

void setup() {
  jdi_display.begin();
  delay(50);
  jdi_display.displayOn();
  jdi_display.frontlightOn();         //Optional depending on the display model
  jdi_display.clearScreen();          //Clear the screen
  printTestCase();
  jdi_display.refresh();
  delay(4000);
  drawChessboard();
  jdi_display.refresh();
  delay(2000);
}

void loop() {
  colorRandomSquare();
  printFPS();
  jdi_display.refresh();              //Actually updates the display
  frames++;

  if(millis() - lastFpsMillis < 1000) return;
  fps = frames / ((millis() - lastFpsMillis) / 1000);
  lastFpsMillis = millis();
  frames = 0;
}

void printTestCase(){
  jdi_display.fillScreen(COLOR_WHITE);
  jdi_display.setTextColor(COLOR_BLACK);
  jdi_display.setTextSize(3);
  jdi_display.setCursor(30, 50);

#ifdef DIFF_LINE_UPDATE
  jdi_display.setTextColor(COLOR_GREEN);
  jdi_display.print("Diff line update");
#else
  jdi_display.setTextColor(COLOR_BLACK);
  jdi_display.print("Full screen update");
#endif
  jdi_display.setCursor(30, 100);
  jdi_display.print(columns * rows);
  jdi_display.setCursor(100, 100);
  jdi_display.print("squares");
  jdi_display.setCursor(240, 100);
  jdi_display.print(SQUARE_SIZE);
  jdi_display.setCursor(280, 100);
  jdi_display.print("x");
  jdi_display.setCursor(300, 100);
  jdi_display.print(SQUARE_SIZE);
}

void drawChessboard(){
  uint16_t color = COLOR_BLACK;
  for(int i = 0; i < columns; i++){
    for(int j = 0; j < rows; j++){
      if((i+j) % 2 == 0) color = COLOR_BLACK;
      else color = COLOR_WHITE;
      jdi_display.fillRect(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, color);
    }
  }
}

void colorRandomSquare(){
  int randColor = random(0, NUMBER_COLORS);
  int randColumn = random(0, columns);
  int randRow = random(0, rows);
  jdi_display.fillRect(randColumn * SQUARE_SIZE, randRow * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, colors[randColor]);
}

void printFPS(){
  jdi_display.fillRect(0, 0, 120, 40, COLOR_WHITE);
  jdi_display.drawRect(0, 0, 120, 40, COLOR_BLACK);
  jdi_display.setTextColor(COLOR_BLACK);
  jdi_display.setTextSize(3);
  jdi_display.setCursor(5, 5);
  jdi_display.print("fps");
  jdi_display.setCursor(65, 5);
  jdi_display.print(fps);
}

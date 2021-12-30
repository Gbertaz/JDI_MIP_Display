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

#define DISPLAY_WIDTH   400         // Display width in pixel
#define DISPLAY_HEIGHT  240         // Display height in pixel

//=================================================================
// Wiring details: https://github.com/Gbertaz/JDI_MIP_Display#wiring
//=================================================================

//===============================
// Wiring example Teensy 4.1
#define PIN_SCS         10          // SPI Chip Select Signal pin
#define PIN_DISP        22          // Display ON/OFF Switching Signal pin
#define PIN_FRONTLIGHT  23          // Frontlight pin. Optional depending on the display model

//===============================
// Wiring example Esp8266 Wemos D1 mini
/*
#define PIN_SCS         15         // D8 GPIO15 SPI Chip Select Signal pin
#define PIN_DISP        4          // D2 GPIO4  Display ON/OFF Switching Signal pin
#define PIN_FRONTLIGHT  5          // D1 GPIO5  Frontlight pin. Optional depending on the display model
*/

//===============================
// Wiring example Esp32 NodeMCU
/*
#define PIN_SCS         5          // GPIO5     SPI Chip Select Signal pin
#define PIN_DISP        21         // GPIO21    Display ON/OFF Switching Signal pin
#define PIN_FRONTLIGHT  22         // GPIO22    Frontlight pin. Optional depending on the display model
*/
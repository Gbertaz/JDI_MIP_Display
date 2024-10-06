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

// #define DISPLAY_WIDTH   400         // Display width in pixel
// #define DISPLAY_HEIGHT  240         // Display height in pixel

//#define USE_ESP32_DMA  // 使用ESP32 DMA
//#define DIFF_LINE_UPDATE   // 差异行更新

//=================================================================
// Wiring details: https://github.com/Gbertaz/JDI_MIP_Display#wiring
//=================================================================

// #define SPI_FREQUENCY   4000000     // SPI frequency in Hz
// #define SPI_CHANNEL     spi0        // SPI channel number
// #define PIN_MISO        D9          // SPI Data Signal pin
// #define PIN_MOSI        D10         // SPI Data Signal pin
// #define PIN_SCK         D8          // SPI Clock Signal pin
// #define PIN_SCS         D7          // SPI Chip Select Signal pin
// #define PIN_DISP        D0          // Display ON/OFF Switching Signal pin
// #define PIN_FRONTLIGHT  -1          // Frontlight pin. Optional depending on the display model

//=================================================================
// 适配老王JDI_Memory LCD屏幕，采用MEGA2560进行驱动
// 分辨率为：144x72
//=================================================================

#define USE_144_72_LCD

#define DISPLAY_WIDTH   144         // Display width in pixel
#define DISPLAY_HEIGHT  72         // Display height in pixel

//控制引脚
#define PIN_SCS         A0          // SPI Chip Select Signal pin
#define PIN_DISP        A1          // Display ON/OFF Switching Signal pin

//SPI设置，不用关注
#define SPI_FREQUENCY   4000000     // SPI frequency in Hz
#define SPI_CHANNEL     spi0        // SPI channel number
#define PIN_MISO        50          // SPI Data Signal pin
#define PIN_MOSI        51          // SPI Data Signal pin
#define PIN_SCK         52          // SPI Clock Signal pin
#define PIN_FRONTLIGHT  -1          // Frontlight pin. Optional depending on the display model
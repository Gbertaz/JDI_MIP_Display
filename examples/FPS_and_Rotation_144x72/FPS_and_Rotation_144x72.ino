//======================================================================
//======================================================================
//
//  这个例子基于FPS_test，增加了屏幕旋转测试，对144x72分辨率的屏幕显示做了优化
//
//
//  接线：            MEGA2560
//       PIN_SCS         A0         
//       PIN_DISP        A1  
//       PIN_MOSI        51         
//       PIN_SCK         52        
//
//  使用前请注意:
//     1) 打开 Display_cfg.h 文件
//     2) 使能 #define USE_144_72_LCD
//     3) 配置 PIN_DISP 和 PIN_SCS 引脚
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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
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

const uint16_t colors[NUMBER_COLORS] = {COLOR_BLACK,  COLOR_BLUE, COLOR_GREEN,
                                        COLOR_CYAN,   COLOR_RED,  COLOR_MAGENTA,
                                        COLOR_YELLOW, COLOR_WHITE};

JDI_MIP_Display jdi_display(0);

int rectHeight = jdi_display.height() / NUMBER_COLORS;
int rectWidth = jdi_display.width() / 2;
int startColor = 0;
int currentColor = 0;

int fps = 0;
unsigned int frames = 0;
unsigned long startMillis = 0;
unsigned long test_rot_Millis = 0;
uint16_t rot_change_flag = 0;

void setup() {
    jdi_display.begin();
    delay(50);
    jdi_display.displayOn();
    jdi_display.clearScreen(); // Clear the screen
    jdi_display.refresh();     // Actually updates the display
    startMillis = millis();
    test_rot_Millis = millis();
}

void loop() {

    //每过一秒使屏幕旋转一次
    if ((millis() - test_rot_Millis) > 1 * 1000) {
        test_rot_Millis = millis();
        if (rot_change_flag==0) {
            rot_change_flag = 1;
            jdi_display.set_direction(0);
            rectHeight = jdi_display.height() / NUMBER_COLORS;
            rectWidth = jdi_display.width() / 2;
        } else if (rot_change_flag==1){
            rot_change_flag = 2;
            jdi_display.set_direction(90);
            rectHeight = jdi_display.height() / NUMBER_COLORS;
            rectWidth = jdi_display.width() / 2;
        }else if (rot_change_flag==2){
            rot_change_flag = 3;
            jdi_display.set_direction(180);
            rectHeight = jdi_display.height() / NUMBER_COLORS;
            rectWidth = jdi_display.width() / 2;
        }else if (rot_change_flag==3){
            rot_change_flag = 0;
            jdi_display.set_direction(270);
            rectHeight = jdi_display.height() / NUMBER_COLORS;
            rectWidth = jdi_display.width() / 2;
        }
    }

    scrollingColors();
    jdi_display.fillCircle(jdi_display.width() / 2, jdi_display.height() / 2,
                           20, COLOR_BLUE);

    int xPos = (jdi_display.width() / 2) - 25;
    int yPos = (jdi_display.height() / 2) - 45;

    jdi_display.setTextColor(COLOR_BLACK, COLOR_WHITE);
    jdi_display.setTextSize(2);
    jdi_display.setCursor(xPos, yPos + 10);
    jdi_display.print("fps");

    if (fps >= 10)
        xPos -= 20;
    jdi_display.setTextColor(COLOR_WHITE);
    jdi_display.setTextSize(2);
    jdi_display.setCursor(xPos + 20, yPos + 35);
    jdi_display.print(fps);
    jdi_display.refresh(); // Actually updates the display

    fps = frames / ((millis() - startMillis) / 1000);
    frames++;
}

void scrollingColors() {

    int y = 0;

    currentColor = startColor;

    for (int i = 0; i < NUMBER_COLORS; i++) {
        jdi_display.fillRect(0, y, rectWidth, rectHeight, colors[currentColor]);
        y += rectHeight;
        currentColor++;
        if (currentColor > NUMBER_COLORS - 1)
            currentColor %= NUMBER_COLORS;
    }

    currentColor = startColor;
    y = jdi_display.height() - rectHeight;
    for (int i = 0; i < NUMBER_COLORS; i++) {
        jdi_display.fillRect(rectWidth, y, rectWidth, rectHeight,
                             colors[currentColor]);
        y -= rectHeight;
        currentColor++;
        if (currentColor > NUMBER_COLORS - 1)
            currentColor %= NUMBER_COLORS;
    }

    if (startColor < NUMBER_COLORS - 1)
        startColor++;
    else
        startColor = 0;
}

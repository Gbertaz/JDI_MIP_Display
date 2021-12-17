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

#include <JDI_MIP_Display.h>

JDI_MIP_Display::JDI_MIP_Display():Adafruit_GFX(DISPLAY_WIDTH, DISPLAY_HEIGHT){
    _scs = PIN_SCS;
    _disp = PIN_DISP;
    _frontlight = PIN_FRONTLIGHT;
}

void JDI_MIP_Display::begin(){
    _background = COLOR_BLACK;
    digitalWrite(_scs, LOW);
    pinMode(_scs, OUTPUT);
    pinMode(_disp, OUTPUT);
    pinMode(_frontlight, OUTPUT);
    memset(&_cmdBuffer[0], 0, sizeof(_cmdBuffer));
    memset(&_cmdBuffer[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(_dispBuffer));
    SPI.begin();
}

void JDI_MIP_Display::refresh()
{
    for(int i=0; i < height(); i++){
        memset(&_cmdBuffer[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(_cmdBuffer));
        memcpy(&_cmdBuffer[0], &_dispBuffer[(width()/2) * i], width()/2);
        sendLineCommand(&_cmdBuffer[0], i);
    }
}

void JDI_MIP_Display::sendLineCommand(char* line_cmd, int line){
    if((line < 0) || (line >= height())){
        return;
    }

    digitalWrite(_scs, HIGH);
    SPI.transfer(CMD_UPDATE);
    SPI.transfer(line + 1);

    for(int i = 0; i < (width()/2); i++){
        SPI.transfer(line_cmd[i]);
    }

    SPI.transfer(0x00);
    SPI.transfer(0x00);
    digitalWrite(_scs, LOW);
}

void JDI_MIP_Display::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if(x < 0 || x >= width() || y < 0 || y >= height()){
        return;
    }

    if(x % 2 == 0){
        _dispBuffer[((width()/2)*y) + (x/2)] &= 0x0F;
        _dispBuffer[((width()/2)*y) + (x/2)] |= (color & 0x0F) << 4;
    }
    else{
        _dispBuffer[((width()/2)*y) + (x/2)] &= 0xF0;
        _dispBuffer[((width()/2)*y) + (x/2)] |= color & 0x0F;
    }
}

void JDI_MIP_Display::setBackgroundColor(uint16_t color){
    _background = color;
}

void JDI_MIP_Display::displayOn(){
    digitalWrite(_disp, HIGH);
}

void JDI_MIP_Display::displayOff(){
    digitalWrite(_disp, LOW);
}

void JDI_MIP_Display::frontlightOn(){
    digitalWrite(_frontlight, HIGH);
}

void JDI_MIP_Display::frontlightOff(){
    digitalWrite(_frontlight, LOW);
}
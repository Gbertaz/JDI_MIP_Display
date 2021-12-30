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
    memset(&_backBuffer[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(_backBuffer));
#ifdef DIFF_LINE_UPDATE
    memset(&_dispBuffer[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(_dispBuffer));
#endif
    SPI.begin();
}

void JDI_MIP_Display::refresh()
{
    for(int i=0; i < height(); i++){
        int lineIdx = HALF_WIDTH * i;
        char *line_cmd;
#ifdef DIFF_LINE_UPDATE
        if(compareBuffersLine(lineIdx) == true) continue;
        memcpy(&_dispBuffer[lineIdx], &_backBuffer[lineIdx], HALF_WIDTH);
        line_cmd = &_dispBuffer[lineIdx];
#else
        line_cmd = &_backBuffer[lineIdx];
#endif
        sendLineCommand(line_cmd, i);
    }
}

bool JDI_MIP_Display::compareBuffersLine(int lineIndex){
#ifdef DIFF_LINE_UPDATE
    for(int i = 0; i < HALF_WIDTH; i++){
        int pixelIdx = lineIndex + i;
        if(_backBuffer[pixelIdx] != _dispBuffer[pixelIdx]) return false;
    }
#endif
    return true;
}

void JDI_MIP_Display::clearScreen(){
    digitalWrite(_scs, HIGH);
    SPI.transfer(CMD_ALL_CLEAR);
    SPI.transfer(0x00);
    digitalWrite(_scs, LOW);
}

void JDI_MIP_Display::sendLineCommand(char* line_cmd, int line){
    if((line < 0) || (line >= height())){
        return;
    }

    digitalWrite(_scs, HIGH);
    SPI.transfer(CMD_UPDATE);
    SPI.transfer(line + 1);

    for(int i = 0; i < HALF_WIDTH; i++){
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

    int pixelIdx = ((width() / 2) * y) + (x / 2);

    if(x % 2 == 0){
        _backBuffer[pixelIdx] &= 0x0F;
        _backBuffer[pixelIdx] |= (color & 0x0F) << 4;
    }
    else{
        _backBuffer[pixelIdx] &= 0xF0;
        _backBuffer[pixelIdx] |= color & 0x0F;
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
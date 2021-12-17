#include <JDI_MIP_Display.h>

const uint16_t colors[8] = {COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE};

JDI_MIP_Display jdi_display;


void setup() {

  Serial.begin(9600);
  
  jdi_display.begin();
  delay(50);
  jdi_display.displayOn();
  jdi_display.frontlightOn();
  jdi_display.fillScreen(COLOR_WHITE);
  jdi_display.refresh();
}

void loop() {
  scrollingColors();
}

int startColor = 0;
int currentColor = 0;
void scrollingColors(){

  int nColors = sizeof(colors) / sizeof(uint16_t);
  int rectHeight = jdi_display.height() / nColors;
  int rectWidth = jdi_display.width() / 2;
  int y = 0;

  currentColor = startColor;
  
  for(int i = 0; i < nColors; i++){
    jdi_display.fillRect(0, y, rectWidth, rectHeight, colors[currentColor]);
    y += rectHeight;
    if(currentColor < nColors) currentColor++;
    else currentColor = 0;
  }

  y = jdi_display.height() - rectHeight;
  for(int i = 0; i < nColors; i++){
    jdi_display.fillRect(rectWidth, y, rectWidth, rectHeight, colors[currentColor]);
    y -= rectHeight;
    if(currentColor < nColors) currentColor++;
    else currentColor = 0;
  }
  
  if(startColor < nColors) startColor++;
  else startColor = 0;

  jdi_display.refresh();
}

# Japan Display Inc. library for Arduino
Arduino library to drive the Memory In Pixel Displays produced by Japan Display Inc.  

The library has been tested only with the display model **LPM027M128B** but it should work with all the JDI MIP Displays with the SPI interface such as **LPM044M141A**, **LPM013M126A** and so on. If you own one of these displays feel free to test the library and send PRs.

# Prerequisites

This library depends on [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) and [Arduino SPI](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI) libraries. So make sure to install those first.

# Usage

### Step 1

Configure the pins according to your wiring scheme by opening [Display_cfg.h](https://github.com/Gbertaz/JDI_MIP_Display/blob/master/Display_cfg.h) and define the following:

```
#define PIN_SCS         10          // SPI Chip Select Signal pin
#define PIN_DISP        22          // Display ON/OFF Switching Signal pin
#define PIN_FRONTLIGHT  23          // Frontlight pin. Optional depending on the display model
```

Also define the width and height in pixel according to your display model:

```
#define DISPLAY_WIDTH   400         // Display width in pixel
#define DISPLAY_HEIGHT  240         // Display height in pixel
```

### Step 2

Include the library:

```
#include <JDI_MIP_Display.h>
```

### Step 3

Create the instance of the display class:

```
JDI_MIP_Display jdi_display;
```

### Step 4

Initialize the display by calling the *begin* function which initializes the buffers and SPI interface. Then turn the display on. Depending on the display model you can also turn the frontlight on or off.

```
jdi_display.begin();
delay(50);
jdi_display.displayOn();
jdi_display.frontlightOn();   // Optional depending on the display model
```

### Step 5

You can now use all the functions defined in the [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) library to draw shapes, text, bitmaps and so on. Please refer to the Adrafruit library documentation.  

Keep in mind that all the drawing functions like *fillCircle*, *drawCircle*, *fillRect*, *print*, *drawBitmap* and so on... just write in the memory buffer, they **don't actually update the display**. In order to update the display you need to call the *refresh* function like so:

```
jdi_display.refresh();
```

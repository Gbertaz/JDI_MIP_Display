# Japan Display Inc. library for Arduino
Arduino library to drive the Memory In Pixel Displays produced by Japan Display Inc.  

The library should also work with the Memory In Pixel Displays produced by Sharp (such as **LS027B7DH01** or **LS044Q7DH01**) because they seem to share the same protocol. The only difference with the JDI Displays is that the latter are 8 bit colors while the Sharp ones are monochrome. 

Please note that the library has been tested only with the JDI display model **LPM027M128B**. If you have a different display model feel free to test the library and send PRs.  

Check out all the [JDI Display models](https://www.j-display.com/english/product/reflective.html).

These displays are readable under direct sunlight because are reflective. They also require less power because in bright environments they don't need a backlight! However if you want to use them in the dark as well you would need a display with a backlight panel (like the model **LPM027M128C** or **LPM013M126C**).  

There is also a different kind of display lighting produced by Azumo: they apply a special thin and transparent film to the front. Check out all the [Azumo displays](https://www.azumotech.com/products/). Some of them are based on Sharp displays, others on JDI display. [This](https://www.azumotech.com/products/2-7-color-display-12380-06/) is the exact display which I bought and used to test the library.

Based on [Tadayuki Okamoto's library](https://os.mbed.com/users/KURETA90/code/ColorMemLCD/).

# Breakout board

Both the Sharp and JDI Displays are ultra slim and compact. They have a 10 pins FPC connector which can be difficult to handle. Some of them have an extra 2 pin connector for the back/front light panel. I have designed a [Breakout board](https://github.com/Gbertaz/JDI_MIP_Display/blob/master/images/breakout_v1.0.png) to make it easy to test the display and turn on/off the light.  

If you want to make the same test board please check the [Schematic, BOM and Gerber](https://github.com/Gbertaz/JDI_MIP_Display/tree/master/breakout/v1.0) files.

Please note that the Breakout board version 1.0 is specifically designed for the JDI MIP Display model **LPM027M128B** so the position of the FPC connectors might change according to the display model. It also has a couple of issues:

1) R3 is too big therefore the light is weak. I have replaced it by soldering a smalled resistor. 
2) The display is powered from 3.3v which is also used to power the frontlight. However there should be a different 5v source to power the frontlight.
3) Capacitors C1 and C2 according to the display datasheet should be 0.1uF which was not in stock when I ordered the board. I then used 100nF instead which should be a problem but keep that in mind.


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
***

Please check the [Examples](https://github.com/Gbertaz/JDI_MIP_Display/tree/master/examples)

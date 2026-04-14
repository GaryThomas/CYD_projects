#include <Arduino.h>

/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD):
   https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/ SET UP INSTRUCTIONS:
   https://RandomNerdTutorials.com/cyd/ 2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display:
   https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and
   https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/ SET UP INSTRUCTIONS:
   https://RandomNerdTutorials.com/esp32-tft/ Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files. The above copyright notice and this permission notice shall
   be included in all copies or substantial portions of the Software.
*/

#include <SPI.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random
   Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD
   TUTORIALS *** FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd/ or
   https://RandomNerdTutorials.com/esp32-tft/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen -
// https://github.com/PaulStoffregen/XPT2046_Touchscreen Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();

// Touchscreen pins
#define XPT2046_IRQ 36  // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 39 // T_OUT
#define XPT2046_CLK 25  // T_CLK
#define XPT2046_CS 33   // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 4

void setup() {
    Serial.begin(115200);
    Serial.println("CYD Template - at your service!");
}

void loop() {}
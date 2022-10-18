#include "common.h"

// Below source will get compiled only
// for hardware configuration option 3
#if HCONFIG == 3

  #include "oled.h"

  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 32 // OLED display height, in pixels

  // Arduino Uno's Digital pins for SPI SSD1306:
  #define OLED_MOSI   9
  #define OLED_CLK   10
  #define OLED_DC    11
  #define OLED_CS    12
  #define OLED_RESET 13

  // Instantiation of SSD1306 Object
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
    OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

  //****************************************************************************//
  // OLED Display initialization function
  //****************************************************************************//
  void initDisplay(void) {
    if(display.begin(SSD1306_SWITCHCAPVCC)) {
      display.clearDisplay();
      display.display();
    }
    else {
      for(;;);        // Stop! Loop forever here
    }
  }


  //****************************************************************************//
  // Helper function to convert UVC Intensity
  // from mW/sq.cm to uW/sq.cm
  //****************************************************************************//
  int intensityUnitChange(float uvcIntensity) {
    return (int)(uvcIntensity * 1000);
  }


  //****************************************************************************//
  // Function to refresh OLED Display with information
  // relevant to recent/up-to-date Energy and Intensity variables
  //****************************************************************************//
  void refreshDisplayMetering(void) {
    display.clearDisplay();                 // Clear entire display

    display.setTextSize(1);                 // 1:1 scale
    display.setTextColor(SSD1306_WHITE);    // White text

    // Print Energy
    display.setCursor(0, 8);                // Upper left

    // Max available numeric place holder is up to 999999.9
    if(energy <= 999999.9)
      display.print(String(energy, 1));     // Print Energy
    else
      display.print("Overflow");            // Error message

    // Print measurement units
    display.setCursor(0, 23);               // Bottom left
    display.print("mJ/sq.cm");              // Energy unit

    display.setCursor(68, 23);              // Bottom middle
    display.print("uW/sq.cm");              // Intensity unit

    // Print Intensity
    display.setTextSize(2);                 // 2x scale
    display.setCursor(68, 0);               // Upper middle
    display.print(String(intensityUnitChange(intensity)));  // Print Intensity

    display.display();                      // Display the buffer
  }


  //****************************************************************************//
  // Function to refresh OLED Display with information
  // relevant to recent/up-to-date UVC wavelength variable
  //****************************************************************************//
  void refreshDisplaySetting(void) {
    display.clearDisplay();                             // Clear entire display

    // Draw rectangle scaled to given wavelength
    display.fillRect(2, 0, (waveLength - 219) * 2, 20, SSD1306_WHITE);

    // Print current wavelength
    display.setTextSize(2);                   // 2x scale
    display.setTextColor(SSD1306_INVERSE);    // Text with inverse color
    display.setCursor(55, 3);                 // The middle area
    display.print(String(waveLength));        // Print wavelength

    // Print wavelength upper, lower limits, and wavelength measurement unit
    display.setTextSize(1);                   // Normal 1:1 scale text
    display.setTextColor(SSD1306_WHITE);      // Draw white text
    display.setCursor(0, 23);                 // Bottom left
    display.print("220");                     // Min wavelength
    display.setCursor(30, 23);                // Bottom middle
    display.print("wavelen, nm");             // UVC wavelength unit
    display.setCursor(110, 23);               // Bottom right
    display.print("280");                     // Max wavelength

    display.display();                        // Display the buffer
  }

  //****************************************************************************//

#endif

#include "common.h"

// Below source will get compiled only
// for hardware configuration options 1 or 2
#if HCONFIG != 3

  #include "sprint.h"
  #include <Arduino.h>

  //****************************************************************************//
  // Function to initialize the Serial.print
  //****************************************************************************//
  void initDisplay(void) {
    Serial.begin(115200);

    // Print header line for subsequent prints
    Serial.print("ADC");      // Raw ADC conversion value (0...1023)
    Serial.print("\t");
    Serial.print("VREF");     // Voltage referfence for ADC, Volt
    Serial.print("\t");
    Serial.print("Vout");     // Calculated sensor's output, Volt
    Serial.print("\t");
    Serial.print("Wave");     // Set UVC wavelength, nm
    Serial.print("\t");
    Serial.print("Resp");     // Sensor's relative responsibility at given wavelength, unitless
    Serial.print("\t");
    Serial.print("Inten");   // Calculated UVC Intensity, uW/sq.cm
    Serial.print("\t");
    Serial.println("Energy"); // Calculated UVC Energy, mJ/sq.cm
  }


  //****************************************************************************//
  // Prints calculated energy/intensity info
  //****************************************************************************//
  void refreshDisplayMetering(void) {
    Serial.print(adcValue);                 // Raw ADC conversion value (0...1023)
    Serial.print("\t");
    Serial.print(AREF, 3);                  // Voltage referfence for ADC, Volt
    Serial.print("\t");
    Serial.print(voltage, 3);               // Calculated sensor's output, Volt
    Serial.print("\t");
    Serial.print(waveLength);               // Set UVC wavelength, nm
    Serial.print("\t");
    Serial.print(relativeResponsivity, 2);  // Sensor's relative responsibility at given wavelength, unitless
    Serial.print("\t");
    Serial.print(intensity * 1000, 1);      // Calculated UVC Intensity, uW/sq.cm
    Serial.print("\t");
    Serial.println(energy, 1);              // Calculated UVC Energy, mJ/sq.cm
  }


  //****************************************************************************//
  // Prints updated UVC wavelength
  //****************************************************************************//
  void refreshDisplaySetting(void) {
    refreshDisplayMetering();
  }

#endif

//****************************************************************************//

// Intensity and energy meter of ultraviolet c-band (UVC) radiations
// For details: https://github.com/wintiltd/uvcMeter
//
//  Created 18 Oct 2022
//  by Bakyt-Bek Murzabaev,
//  b.b.murzabaev@gmail.com

#include <Event.h>
#include <Timer.h>      // https://github.com/JChristensen/Timer
#include <OneButton.h>  // https://github.com/mathertel/OneButton

#include "common.h"             // Global variables
#include "fsm.h"                // Finite State Machine (FSM)
#include "sensor.h"             // Custom functions for Sensor GUVC-T21GH

// Selective include depending on
// the hardware configuration set in "common.h"
#if HCONFIG == 3
  #include "oled.h"               // Functions to work with SSD1306 OLED Display
#else
  #include "sprint.h"             // Functions to output on computer serial port
#endif


OneButton btn = OneButton(      // Instance / OneButton Object
  BUTTON_PIN,                   // Input pin for the button
  true,                         // Button is active LOW
  true                          // Enable internal pull-up resistor
);

Timer timer;                    // Instance / Timer Object

// Initialization of global variables
// ref. to "common.h"
float  intensity = 0;               // UVC Intensity, mW/sq.cm
float  energy = 0;                  // UVC Energy, mJ/sq.cm
int    waveLength = 254;            // Default UVC Light wavelength, nm
int prevWaveLength = 254;           // Used in energy reset
float  relativeResponsivity = 0.91; // Sensor's relat. responsivity for 254 nm
float  voltage = 0;                 // Voltage corresp. to raw ADC Value

// For ADC work in this module
boolean working = false;            // false = ADC is ready for new conversion
                                    // true = ADC conversion is ongoing
int adcValue = 0;                   // Raw ADC value (0...1023)

//****************************************************************************//
// Initial setup
//****************************************************************************//
void setup() {
  // Attach apprpopriate FSM event funtions for relevant "interruptions"
  btn.attachClick(FSM_singleClick);
  btn.attachDoubleClick(FSM_doubleClick);
  btn.attachDuringLongPress(FSM_longPress);
  timer.every(CALC_TIME, FSM_timeToCalc);
  timer.every(REFRESH_TIME, FSM_timeToRefresh);

  initDisplay();                    // Initialize Display or Serial
  FSM_Init();                       // Initialize FSM

  // Set ADC Registers
  ADCSRA =  bit (ADEN);                                 // Turn ADC on
  ADCSRA |= bit (ADPS0) |  bit (ADPS1) | bit (ADPS2);   // Prescaler of 128

  // Reference voltage source for ADC conversion
  // and ADC channel selection
  #if HCONFIG == 1
    ADMUX |= (1<<REFS0);                            // Select Vref=AVcc
    ADMUX = (ADMUX & 0xF0) | (SENSOR_PIN  & 0x0F);  // Select ADC channel
  #else
    // AREF (external reference voltage)
    ADMUX |= (0<<REFS1) | (0<<REFS0);               // Select Vref=AREF
    ADMUX = (ADMUX & 0xF0) | (SENSOR_PIN  & 0x0F);  // Select ADC channel
  #endif
}

//****************************************************************************//
// Main Loop
//****************************************************************************//
void loop() {
  if(!working) {                    // Check whether ADC conversion is ongoing
    bitSet (ADCSRA, ADSC);          // Start ADC conversion
    working = true;                 // Set the flag: ADC conversion is ongoing
  }

  // Check for other events
  btn.tick();                       // Testing for OneButton events
  timer.update();                   // Testing for Timer events

  if (bit_is_clear(ADCSRA, ADSC)) { // Check whether ADC conversion is done
                                    // ADC clears the bit when done
    adcValue = ADC;                 // Read raw ADC value
    working = false;                // Clear the flag: ADC is ready for new conversion
  }
}
//****************************************************************************//

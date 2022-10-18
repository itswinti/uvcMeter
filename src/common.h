#ifndef COMMON_H
#define COMMON_H

// HARDWARE CONFIGURATION OPTION
// Uncomment the option related to your circuit assembly

//#define HCONFIG       1           // Hardware Configuration #1
//#define HCONFIG       2           // Hardware Configuration #2
#define HCONFIG       3           // Hardware Configuration #3

// External hardware connection
#define BUTTON_PIN    4             // Arduino Uno's Digital Pin 4
                                    // to which the button is attached.
                                    // It shorts to ground when pressed
#define SENSOR_PIN    0             // Arduino Uno's Analog Pin A0 to which
                                    // UVC Sensor's Vout pin is attached

// Periods for timers to raise events
#define CALC_TIME     500           // UVC Energy integration time period, ms
#define REFRESH_TIME  1000          // Display refresh rate, ms

// Voltage Reference for ADC conversion depending on
// selected above Hardware Configuration Option
#if HCONFIG == 1
  #define AREF        5.0           // AVcc (Volt)
#else
  #define AREF        2.495         // External reference voltage (Volt)
                                    // applied at AREF pin of Arduino Uno
#endif

extern float  intensity;            // UVC Intensity, mW/sq.cm
extern float  energy;               // UVC Energy, mJ/sq.cm
extern int    waveLength;           // UVC Light wavelength, nm
extern int prevWaveLength;          // Used in energy reset
extern float  relativeResponsivity; // UVC sensor's relative responsivity
extern int adcValue;                // Raw ADC value (0...1023)
extern float  voltage;              // Voltage corresp. to raw ADC Value


//****************************************************************************//
#endif /* COMMON_H */
//****************************************************************************//

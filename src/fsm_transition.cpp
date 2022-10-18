#include "fsm.h"
#include "common.h"
#include "sensor.h"

// Selective include depending on
// the hardware configuration set in "common.h"
#if HCONFIG == 3
  #include "oled.h"   // Functions to work with SSD1306 OLED Display
#else
  #include "sprint.h" // Functions to output on computer serial port
#endif

//****************************************************************************//
// Transition function "calculateIntensityAndEnergy"
//****************************************************************************//
void FSM_calculateIntensityAndEnergy (void)
{
  // Raw ADC to Voltage conversion @ AREF Voltage Reference
  voltage = ((float)adcValue + 0.5 ) / 1024.0 * AREF;

  // UVC Intensity and Energy calculations
  // Refer to sensor.h / sensor.cpp files for more details
  intensity = getUvcIntensity(voltage);
  energy += getUvcEnergy(intensity, CALC_TIME/1000.0);
}


//****************************************************************************//
// Transition function "refreshDisplay"
//****************************************************************************//
void FSM_refreshDisplay (void)
{
  switch(ActState) {
    case UVCMETERING:
      refreshDisplayMetering();
      break;
    case WAVELENSETTING:
      refreshDisplaySetting();
      break;
    default:
      refreshDisplayMetering();
      break;
  }
}


//****************************************************************************//
// Transition function "resetEnergy"
//****************************************************************************//
void FSM_resetEnergy (void)
{
  energy = 0;

  FSM_refreshDisplay();
}


//****************************************************************************//
// Transition function "moveToSetting"
//****************************************************************************//
void FSM_moveToSetting (void)
{
  refreshDisplaySetting();
}


//****************************************************************************//
// Transition function "waveLengthIncrement"
//****************************************************************************//
void FSM_waveLengthIncrement (void)
{
  waveLength++;

  // GenUV UV Sensor Module GUVC-T21GH is sensitive to UVC radiation
  // within 220 nm to 280 nm wavelength only
  // Hence, we need to limit the wavelength to stay within this range
  if(waveLength > 280)
    waveLength = 220;

  FSM_refreshDisplay();
}


//****************************************************************************//
// Transition function "moveToMetering"
//****************************************************************************//
void FSM_moveToMetering (void)
{
  // Energy calculated so far might not be anymore relevant
  // if wavelength has changed in the setting mode, hence
  if(waveLength != prevWaveLength) {
    setRelativeResponsivity(waveLength);  // New Relative Responsivity
    energy = 0;                           // Reset energy counter
    prevWaveLength = waveLength;          // Store new for next check
  }

  FSM_refreshDisplay();
}


//****************************************************************************//

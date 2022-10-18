#include "sensor.h"
#include "common.h"
#include <stdio.h>

//****************************************************************************//
// Sensor's (relative responsivity x 100) LookUp Table
// for wavelength ranging from 220 nm to 280 nm with a step of 1 nm
//****************************************************************************//
uint8_t responsivityArr[61] = {8,  9, 12, 14, 18, 20, 21, 27, 28, 34, 37, 38,
                           44, 44, 49, 51, 55, 58, 61, 65, 67, 70, 72, 74,
                           76, 78, 80, 81, 82, 85, 85, 87, 88, 89, 91, 91,
                           92, 94, 95, 96, 97, 97, 98, 98, 99, 99, 97, 93,
                           89, 86, 80, 77, 71, 67, 56, 50, 42, 41, 29, 21, 17};


//****************************************************************************//
// Sensor's Relative Responsivity = responsivityArr[waveLength - 220) / 100;
//****************************************************************************//
void setRelativeResponsivity(int uvcWavelength) {
  relativeResponsivity = responsivityArr[uvcWavelength - 220] / 100.0;
}


//****************************************************************************//
// Returns UVC intensity (mW/sq.cm) based on
// sensor's Vout and adjusted by UVC sensor's relative responsivity
//****************************************************************************//
float getUvcIntensity(float sensorVoltage) {
  return (sensorVoltage / (0.71 * relativeResponsivity));
}


//****************************************************************************//
// Returns UVC energy (mJ/sq.cm) based on
// intensity (mW/sq.cm) and exposed time (seconds)
//****************************************************************************//
float getUvcEnergy(float uvcIntensity, float exposeTime) {
  return uvcIntensity * exposeTime;
}

//****************************************************************************//

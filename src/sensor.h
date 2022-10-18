#ifndef SENSOR_H
#define SENSOR_H

void setRelativeResponsivity(int uvcWavelength);
                        // Sensor's Relative Responsivity (unitless)
                        // based on UVC wavelength, nm

float getUvcIntensity(float sensorVoltage);
                        // Calculates the UVC light intensity (mW/sq.cm)
                        // based on the sensor's Vout (Voltage)
                        // in accordance with the sensor's datasheet
                        // sensor: GenUV UV Sensor Module GUVC-T21GH

float getUvcEnergy(float uvcIntensity, float exposeTime);
                        // Calculates the UVC Energy (mJ/sq.cm) based on
                        // UVC intensity (mW/sq.cm), and
                        // exposed time (seconds)

//****************************************************************************//
#endif /* SENSOR_H */
//****************************************************************************//

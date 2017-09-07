#include "scale.h"
#include "logger.h"
#include "Arduino.h"
#include "HX711.h"
HX711 scale;
float calibration_factor = 184685.00;
void Scale::Init()
{
  scale.begin(D6, D5);
  scale.set_scale(calibration_factor); 
}

int Scale::GetGrams()
{
  Logger::LogLn("GetGrams()");
  int scaleReadingGrams = int(scale.get_units() * 0.453592 * 1000);
  return scaleReadingGrams;
}


#include "barista.h"
#include "scale.h"
#include "logger.h"
#include "cafe.h"

void Barista::Init()
{
  Logger::LogLn("Barista::Init");
  Barista::b = Barista();
  Scale::Init();
}

float GramsToCups(int grams)
{
  float coffeeCups = grams/COFFEE_FLUID_GRAMS;
  Logger::Log("coffee cups remaining: ");
  Logger::LogLn(String(coffeeCups));
  Serial.println(coffeeCups);

  return coffeeCups;
}

void Barista::CheckScale()
{
  int scaleReading = Scale::GetGrams();
  if (scaleReading >= 0)
  {
    Logger::LogLn(String(scaleReading));

    float coffeeCups = scaleReading/float(COFFEE_FLUID_GRAMS);
    Logger::Log("coffee cups remaining: ");
    Logger::LogLn(String(coffeeCups));

    Cafe::NotifyCoffeeLevel(scaleReading, coffeeCups);
  }
}

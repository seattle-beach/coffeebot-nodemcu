#include <Arduino.h>
#include "barista.h"
#include "cafe.h"

#include "env.h"
#include "logger.h"
void setup()
{
  Barista::Init();

  BlinkOff();

  Barista::CheckScale();
  Logger::LogLn("Sleeping for 15 seconds");
  ESP.deepSleep(15 * 1e6, WAKE_RF_DEFAULT);
  delay(100);
}

void loop()
{
  Logger::LogLn("Should never get here");
}

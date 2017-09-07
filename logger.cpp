#include "logger.h"
#include "Arduino.h"

bool Logger::Enabled = true;
bool Logger::IsInitialized = false;
const int Logger::Baud = 115200;

void Logger::Enable()
{
  Logger::Enabled = true;
}

void Logger::Disable()
{
  Logger::Enabled = false;
}

void Logger::Init(int baud)
{
  Serial.begin(baud);
}

void Logger::Log(String msg)
{
  if (Logger::Enabled)
  {
    if (!Logger::IsInitialized)
    {
      Logger::Init(Logger::Baud);
      Logger::IsInitialized = true;
    }

    Serial.print(msg);
  }
}

void Logger::LogLn(String msg)
{
  Logger::Log(msg);
  Serial.println();
}


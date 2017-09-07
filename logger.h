#ifndef LOGGER_H
  #define LOGGER_H

  #include "Arduino.h"

  class Logger
  {
    public:
      static void Disable();
      static void Enable();
      static void Log(String msg);
      static void LogLn(String msg);
    private:
      static void Init(int baud);
      static bool Enabled;
      static bool IsInitialized;
      static const int Baud;
  };
#endif //LOGGER_H

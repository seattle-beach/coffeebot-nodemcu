#include "env.h"
#include "logger.h"
#include "Arduino.h"
#include "EEPROM.h"

bool Env::IsInitialized = false;
void Env::Init()
{
  Logger::LogLn("Initializing EEPROM");
  EEPROM.begin(512);
}

void Env::Load(BaristaConfig& bconf)
{
  Logger::LogLn("Loading BaristaConfig");
  if (!Env::IsInitialized)
  {
    Env::Init();
    Env::IsInitialized = true;
  }
  
  Logger::LogLn("Loading from EEPROM");
  int addr;
  for (int m = 0; m < MAX_HEADER_LEN; m++, addr++)
  {
    bconf.header[m] = char(EEPROM.read(addr));
  }
  for (int m = 0; m < MAX_WIFI_SSID; m++, addr++)
  {
    bconf.wifi_ssid[m] = char(EEPROM.read(addr));
  }
  for (int m = 0; m < MAX_WIFI_PASSWORD; m++, addr++)
  {
    bconf.wifi_password[m] = char(EEPROM.read(addr));
  }
  for (int m = 0; m < MAX_URL_LEN; m++, addr++)
  {
    bconf.url[m] = char(EEPROM.read(addr));
  }
  for (int m = 0; m < MAX_SSL_CERT_FP_LEN; m++, addr++)
  {
    bconf.cert_fp[m] = char(EEPROM.read(addr));
  }
}

void Env::Save(const BaristaConfig& bconf)
{
  Logger::LogLn("saving BaristaConfig:");
  if (!Env::IsInitialized)
  {
    Env::Init();
    Env::IsInitialized = true;
  }

  Env::LogConfig(bconf);

  Logger::LogLn("Clearing EEPROM");
  int addr;
  for (addr = 0; addr < sizeof(BaristaConfig); addr++)
  {
    EEPROM.write(addr, 0);
  }

  Logger::LogLn("Saving to EEPROM");
  addr = 0;
  for (int m = 0; m < MAX_HEADER_LEN; m++, addr++)
  {
    EEPROM.write(addr, bconf.header[m]);
  }
  for (int m = 0; m < MAX_WIFI_SSID; m++, addr++)
  {
    EEPROM.write(addr, bconf.wifi_ssid[m]);
  }
  for (int m = 0; m < MAX_WIFI_PASSWORD; m++, addr++)
  {
    EEPROM.write(addr, bconf.wifi_password[m]);
  }
  for (int m = 0; m < MAX_URL_LEN; m++, addr++)
  {
    EEPROM.write(addr, bconf.url[m]);
  }
  for (int m = 0; m < MAX_SSL_CERT_FP_LEN; m++, addr++)
  {
    EEPROM.write(addr, bconf.cert_fp[m]);
  }

  Logger::LogLn("Committing EEPROM");
  EEPROM.commit();
  yield();
}

void Env::LogConfig(const BaristaConfig& bconf)
{
  Logger::Log("conf.header: ");
  Logger::LogLn(bconf.header);
  Logger::Log("conf.wifi_ssid: ");
  Logger::LogLn(bconf.wifi_ssid);
  Logger::Log("conf.wifi_password: ");
  Logger::LogLn(bconf.wifi_password);
  Logger::Log("conf.url: ");
  Logger::LogLn(bconf.url);
  Logger::Log("conf.cert_fp: ");
  Logger::LogLn(bconf.cert_fp);
}

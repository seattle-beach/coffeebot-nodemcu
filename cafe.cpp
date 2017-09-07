#include "cafe.h"
#include "env.h"
#include "logger.h"
#include "Arduino.h"

// https://github.com/esp8266/Arduino/releases/tag/2.4.0-rc1
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void BlinkOn()
{
    digitalWrite(LED_BUILTIN, LOW);
}

void BlinkOff()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

void ConnectWifi()
{
  WiFi.persistent(false);

  Logger::Log("MAC address is ");
  Logger::LogLn(WiFi.macAddress());

  BaristaConfig bconf;
  Env::Load(bconf);

  WiFiMulti.addAP(bconf.wifi_ssid, bconf.wifi_password);
  
  Logger::Log("Connecting");
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Logger::Log(".");
  }
  Logger::LogLn("Connected!");
  Logger::LogLn(WiFi.localIP().toString());
}

void TestConnection()
{
  HTTPClient http;

  BaristaConfig bconf;
  Env::Load(bconf);

  http.begin(bconf.url, bconf.cert_fp);
  int statusCode = http.GET();
  Logger::Log("http.GET() returned: ");
  Logger::LogLn(String(statusCode));

  if (statusCode < 0)
  {
    http.end();
    return;
  }

  String resp = http.getString();
  Logger::Log("response: ");
  Logger::LogLn(resp);
  http.end();
}

bool Cafe::Ping()
{
  HTTPClient http;

  BaristaConfig bconf;
  Env::Load(bconf);

  ConnectWifi();

  String pingUrl = String(bconf.url) + String("/ping");
  Logger::LogLn("Ping URL: " + pingUrl);
  http.begin(pingUrl, bconf.cert_fp);
  int statusCode = http.GET();
  Logger::Log("http.GET() returned: ");
  Logger::LogLn(String(statusCode));

  if (statusCode < 0)
  {
    http.end();
    return false;
  }

  String resp = http.getString();
  Logger::Log("response: ");
  Logger::LogLn(resp);
  http.end();

  return resp == "pong";
}

void Cafe::NotifyCoffeeLevel(int grams, float cups)
{
  HTTPClient http;

  BaristaConfig bconf;
  Env::Load(bconf);

  ConnectWifi();

  String pingUrl = String(bconf.url) + String("/report");
  Logger::LogLn("Ping URL: " + pingUrl);
  http.begin(pingUrl, bconf.cert_fp);
  http.addHeader("Content-Type", "application/json");
  int statusCode = http.POST("{\"devId\":\"NodeMCU\",\"qty\":" + String(grams) + "}");
  Logger::Log("http.POST() returned: ");
  Logger::LogLn(String(statusCode));

  if (statusCode < 0)
  {
    http.end();
    return;
  }

  String resp = http.getString();
  Logger::Log("response: ");
  Logger::LogLn(resp);
  http.end();
}


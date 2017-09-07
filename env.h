#ifndef ENV_H
    #define ENV_H

    #define MAX_HEADER_LEN 7
    #define MAX_URL_LEN 100
    #define MAX_SSL_CERT_FP_LEN 100
    #define MAX_WIFI_SSID 50
    #define MAX_WIFI_PASSWORD 50

    struct BaristaConfig
    {
      char header[MAX_HEADER_LEN];
      char wifi_ssid[MAX_WIFI_SSID];
      char wifi_password[MAX_WIFI_PASSWORD];
      char url[MAX_URL_LEN];
      char cert_fp[MAX_SSL_CERT_FP_LEN];
    };

    class Env
    {
      public:
        static void Save(const BaristaConfig& bconf);
        static void Load(BaristaConfig& bconf);
      private:
        static void Init();
        static bool IsInitialized;
        static void LogConfig(const BaristaConfig& bconf);
    };
#endif //ENV_H


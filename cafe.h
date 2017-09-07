#ifndef CAFE_H
    #define CAFE_H
    void BlinkOn();
    void BlinkOff();

    void ConnectWifi();
    void TestConnection();

    class Cafe
    {
      public:
        static bool Ping();
        static void NotifyCoffeeLevel(int grams, float cups);
    };
#endif //CAFE_H

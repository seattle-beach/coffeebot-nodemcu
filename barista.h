#ifndef BARISTA_H
  #define BARISTA_H
  class Barista
  {
    public:
      static void Init();
      static void CheckScale();
    private:
      static Barista b;
  };
#endif //BARISTA_H

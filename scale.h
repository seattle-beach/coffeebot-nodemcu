#ifndef SCALE_H
  #define SCALE_H

#define COFFEE_POT_GRAMS 1450
#define MAX_COFFEE_POT_GRAMS 1860
#define MAX_POT_INCLUSIVE_GRAMS  3310

#define COFFEE_MUG_GRAMS 330
#define COFFEE_FLUID_GRAMS  255 // 9oz

  class Scale
  {
    public:
      static void Init();
      static int GetGrams();
  };
#endif //SCALE_H

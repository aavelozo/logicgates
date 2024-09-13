#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "BaseScreen.h"

struct BaseScreen{
  void drawBackButton();
  virtual void draw(char* params[] = nullptr);
};

#endif //BASESCREEN_H
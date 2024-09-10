#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "BaseScreen.h";

struct BaseScreen{
  void drawBackButton();
  virtual void draw();
};

#endif //BASESCREEN_H
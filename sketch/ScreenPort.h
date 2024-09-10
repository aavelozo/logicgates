#pragma once;

#ifndef SCREENPORT_H
#define SCREENPORT_H

#include <Arduino.h>;
#include "BaseScreen.h";

struct ScreenPort : public BaseScreen{
  static const byte SCREEN_ID = 2;
  void draw() override;
};

#endif // SCREENPORT_H
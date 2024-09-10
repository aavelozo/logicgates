#pragma once;

#ifndef SCREENLEARNING_H
#define SCREENLEARNING_H

#include <Arduino.h>;
#include "BaseScreen.h";

struct ScreenLearning : public BaseScreen{
  static const byte SCREEN_ID = 1;
  void drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção");
  void draw() override;
};

#endif // SCREENLEARNING_H
#pragma once;

#ifndef SCREENINITIALMENU_H
#define SCREENINITIALMENU_H

#include <Arduino.h>;
#include "BaseScreen.h";

struct ScreenInitialMenu : public BaseScreen{
  static const byte SCREEN_ID = 0;
  void drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção");
  void draw() override;
};

#endif // SCREENINITIALMENU_H
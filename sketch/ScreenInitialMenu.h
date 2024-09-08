#pragma once;

#ifndef SCREENINITIALMENU_H
#define SCREENINITIALMENU_H

#include "BaseScreen.h";

struct ScreenInitialMenu : public BaseScreen{
  void drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção");
  void draw() override;
};

#endif // SCREENINITIALMENU_H
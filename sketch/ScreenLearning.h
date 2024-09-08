#pragma once;

#ifndef SCREENLEARNING_H
#define SCREENLEARNING_H

#include "BaseScreen.h";

struct ScreenLearning : public BaseScreen{
  void drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção");
  void draw() override;
};

#endif // SCREENLEARNING_H
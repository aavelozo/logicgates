#pragma once;

#ifndef TSCONTROLLER_H
#define TSCONTROLLER_H


#include <MCUFRIEND_kbv.h>  // Biblioteca MCUFRIEND_kbv
#include <TouchScreen.h>   // Biblioteca para touchscreen

//para armazenar informações referente ao dimensionmanto (bounds) de textos em tela
struct TextInfo{
  int x, y;  // Variáveis para armazenar a posição do canto superior esquerdo
  int w, h;  
};

struct TSController{
  // Definição dos pinos do TFT
  static const int LCD_CS     = A3;
  static const int LCD_CD     = A2;
  static const int LCD_WR     = A1;
  static const int LCD_RD     = A0;
  static const int LCD_RESET  = A4;

  // Definição dos pinos do touchscreen
  static const int TS_XP  = 8;  // Substitua pelo pino correto
  static const int TS_YP  = A3;  // Substitua pelo pino correto
  static const int TS_XM  = A2;  // Substitua pelo pino correto
  static const int TS_YM  = 9;  // Substitua pelo pino correto

  // Definição das variáveis de calibração do touchscreen
  static const int TS_MINX  = 100;
  static const int TS_MAXX  = 920;
  static const int TS_MINY  = 120;
  static const int TS_MAXY  = 920;

  // Configuração do touchscreen
  static TouchScreen ts;

  // Criação do objeto TFT
  static MCUFRIEND_kbv tft;
  
  static void init();
  static TextInfo TSController::drawCenteredText(const char* text, int y = 0, float centerX = TSController::tft.width() / 2, int textSize = 2, int color = TFT_WHITE);
};

#endif // TSCONTROLLER_H

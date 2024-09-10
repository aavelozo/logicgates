#pragma once;

#ifndef EVENTRECEPTOR_H
#define EVENTRECEPTOR_H

#include "Utils.h";
#include "BaseScreen.h";

struct EventReceptor;//forward declaration
extern EventReceptor* lastEventReceptor;

//para instanciar elementos desenhados em tela que precisam receber eventos de toque (clique)
struct EventReceptor {
  UIPoint centerPoint;
  int distance;
  void (*onClick)();
  EventReceptor(int x,int y,int pDist);

  //checa se o elemento foi clicado, basedo nos parametros do construtor, sendo um ponto central e um raio
  bool checkClickEvent(UIPoint point);
  EventReceptor* prev;
};

void clearAllEventReceptors();

#endif // EVENTRECEPTOR_H

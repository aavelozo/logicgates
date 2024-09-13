#ifndef EVRcpt_H
#define EVRcpt_H

#include "Utils.h"
#include "BaseScreen.h"

struct EVRcpt;//forward declaration
extern EVRcpt* lastEVRcpt;

//para instanciar elementos desenhados em tela que precisam receber eventos de toque (clique)
struct EVRcpt {
  DPoint centerPoint;
  double distance;
  void (*onClick)();
  EVRcpt(double x,double y,double pDist, void (*pOnClick)() = nullptr);

  //checa se o elemento foi clicado, basedo nos parametros do construtor, sendo um ponto central e um raio
  bool checkClickEvent(DPoint point);
  EVRcpt* prev;
};

void clearAllEVRcpts();

#endif // EVRcpt_H

#include "OrGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
OrGate::OrGate(
  double pX,
  double pY,
  double pSize,
  byte pConnectorCount,
  bool pVertical,
  int pLineColor,
  double pLineWidth,
  double pAspectRatio,
  double pBaseSizePerc,
  double pConnectorSize,
  double pWidth,
  double pConnectorMargin
) :
  Gate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) {}

void OrGate::drawBody() {
  
};
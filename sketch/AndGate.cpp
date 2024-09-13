#include "AndGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
AndGate::AndGate(
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

void AndGate::drawBody() {
  double arcHeightPerc = 0;
  if (baseSizePerc != DEFAULT_GATE_BASE_SIZE_PERC) {
    arcHeightPerc = 1-baseSizePerc;
  } else {
    arcHeightPerc = 1/connectorCount;
  }  
  if (arcHeightPerc < 0.2) {
    arcHeightPerc = 0.2;
  }
  double arcHeight = size * arcHeightPerc;
  
  double r = 0;
  double baseAdjust = 0;
  if (arcHeight >= width/2) {
    r = width / 2;
    //r = r-1; //causa erro
    Serial.println("xxc"+String(r));
    baseAdjust = arcHeight - r;
    //r = r - 0;
  } else {
    r = (arcHeight * arcHeight + pow(width/2,2)) / (2 * arcHeight);   
    //r = r - 0; 
  }  
  
  double py2 = pow(r,2);
  py2 = pow(r, 2) - pow(width / 2, 2);
  /*if (py2 > 0) {
    py2 = sqrt(py2);
  } else {
    py2 = 0;
  }*/
  double arcAngle = getArcAngle(width,r);
  if (vertical) {
    SCtrl::tft.fillRect(x,y-lineWidth,width,lineWidth,lineColor); //base line
    SCtrl::tft.fillRect(x,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //left line
    SCtrl::tft.fillRect(x+width-lineWidth,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //rigth line        
    py2 = y - size + arcHeight + py2;
    double startAngle = 270-(arcAngle / 2);
    for (int i = 0; i < lineWidth ; i++) {
      SCtrl::drawSmoothArc(x+(width / 2),py2-baseAdjust+i/8,r-i,startAngle,startAngle+arcAngle,lineColor);    
    }
  } else {
    /*SCtrl::tft.fillRect(x,y,lineWidth,width,lineColor);
    SCtrl::tft.fillRect(x,y,size-arcHeight+baseAdjust,lineWidth,lineColor); //left line
    SCtrl::tft.fillRect(x,y+width,size-arcHeight+baseAdjust,lineWidth,lineColor); //rigth line
    py2 = x + (size - arcHeight) - py2;
    double startAngle = 0-(arcAngle/2)+0;
    SCtrl::drawSmoothArc(py2+baseAdjust,y+(width/2),r,startAngle,startAngle+arcAngle+0,lineColor);*/
  }
};
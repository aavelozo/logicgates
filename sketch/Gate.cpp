#include "Gate.h"


Gate::Gate(
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
  x(pX),
  y(pY),
  size(pSize),  
  connectorCount(pConnectorCount),
  vertical(pVertical),
  lineColor(pLineColor),
  lineWidth(pLineWidth),
  aspectRatio(pAspectRatio),
  baseSizePerc(pBaseSizePerc),
  connectorSize(pConnectorSize),    
  width(pWidth),
  connectorMargin(pConnectorMargin)  
{
  if (pSize != DEFAULT_GATE_SIZE) {
    if (pWidth == DEFAULT_GATE_WIDTH) {
      width = pSize * pAspectRatio;
      connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;
    } 
    if (pConnectorSize == DEFAULT_GATE_CONNECTOR_SIZE) {
      connectorSize = width * DEFAULT_GATE_CONNECTOR_SIZE_PERC;
    }
  }
}

Gate::~Gate() {
  // Limpeza, se necessária
};


void Gate::drawConnector(byte position) { 
  double connMargin = connectorMargin;
  if (position > 0) {            
    connMargin = connMargin + (position * (width - (connMargin * 2.0)) / (connectorCount - 1.0));    
  } 
  if (lineWidth > 1) {
    connMargin = connMargin - lineWidth / 2.0;
  }
  if (vertical) {
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(x + connMargin+i,y,x + connMargin+i,y + connectorSize, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + connMargin,y,x + connMargin,y + connectorSize, lineColor);
    }
  } else {
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(x, y + connMargin + i,x - connectorSize,y + connMargin+i, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x, y + connMargin,x - connectorSize,y + connMargin, lineColor);
    }
  }
};

void Gate::drawOutputConnector() {   
  if (vertical) {
    if (lineWidth > 1) {
      double pInit = x + (width / 2.0 ) - (lineWidth / 2.0);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(pInit+i ,y - size - connectorSize,pInit+i,y - size , lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + (width / 2.0 ) ,y - size - connectorSize,x + (width / 2.0 ),y - size , lineColor);
    }
  } else {
    if (lineWidth > 1) {
      double pInit = y + (width / 2.0) - (lineWidth / 2.0);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(x + size ,pInit + i,x + size + connectorSize,pInit + i, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + size ,y + (width/2.0),x + size + connectorSize,y + (width/2.0), lineColor);
    }
  }
};

void Gate::drawBody() {
  //to override
}

void Gate::draw() {
  //int portSize = 250;
  for(byte i = 0; i < connectorCount; i++) {
    drawConnector(i);
  }
  drawOutputConnector();
  drawBody();
};
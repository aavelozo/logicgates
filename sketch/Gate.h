#ifndef GATE_H
#define GATE_H

#include <Arduino.h>
#include "SCtrl.h"

#define DEFAULT_GATE_SIZE 150.0
#define DEFAULT_GATE_CONNECTOR_COUNT 2
#define DEFAULT_GATE_VERTICAL_DIRECTION true
#define DEFAULT_GATE_LINE_COLOR TFT_WHITE
#define DEFAULT_GATE_LINE_WIDTH 1.0
#define DEFAULT_GATE_ASPECT_RATIO 0.0
#define DEFAULT_GATE_BASE_SIZE_PERC 0.0
#define DEFAULT_GATE_BASE_CURVE_PERC 0.3

#define DEFAULT_GATE_CONNECTOR_MARGIN_PERC 0.1
#define DEFAULT_GATE_CONNECTOR_SIZE_PERC 0.3
#define DEFAULT_GATE_WIDTH DEFAULT_GATE_SIZE * DEFAULT_GATE_ASPECT_RATIO
#define DEFAULT_GATE_CONNECTOR_SIZE DEFAULT_GATE_SIZE * DEFAULT_GATE_CONNECTOR_SIZE_PERC
#define DEFAULT_GATE_CONNECTOR_MARGIN DEFAULT_GATE_WIDTH * DEFAULT_GATE_CONNECTOR_MARGIN_PERC




struct Gate{ 

  double x;
  double y;
  double size;
  byte connectorCount;
  bool vertical;
  int lineColor;
  double lineWidth;
  double aspectRatio;
  double baseSizePerc;
  double connectorSize;
  double width;  
  double connectorMargin;

  Gate(
    double pX                = 150.0, 
    double pY                = 250.0,
    double pSize             = DEFAULT_GATE_SIZE,
    byte pConnectorCount     = DEFAULT_GATE_CONNECTOR_COUNT,	
    bool pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
    int pLineColor           = DEFAULT_GATE_LINE_COLOR,
    double pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
    double pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
    double pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
    double pConnectorSize    = DEFAULT_GATE_CONNECTOR_SIZE,
    double pWidth            = DEFAULT_GATE_WIDTH,
    double pConnectorMargin  = DEFAULT_GATE_CONNECTOR_MARGIN
  );
  virtual ~Gate();
  void drawConnector(byte position);
  void drawOutputConnector();
  void draw();
  virtual void drawBody();
};

#endif //GATE_H
#include "ScreenPort.h"
#include "Utils.h"
#include "SCtrl.h"
#include "AndGate.h"
#include "OrGate.h"

void drawRandomAndPort(){
  double minX = 0.0;
  double maxX = SCtrl::tft.width() * 0.8;
  double minY = 0.0;
  double maxY = SCtrl::tft.height(); 
  double minS = 50.0;
  double maxS = SCtrl::tft.width() * 0.8;
  while(true) {
    bool vertical = random(0, 2) == 1;
    maxX = SCtrl::tft.width() * 0.8;
    if (vertical) {
      minY = 100.0;
    } else {
      minY = 0.0;
      maxX = SCtrl::tft.width() * 0.60;
    }
    double xPos = random(minX,maxX);
    double yPos = random(minY,maxY);
    byte connectors = random(2,8);
    if (vertical) {
      maxS = SCtrl::tft.height() - yPos;
    } else {
      maxS = SCtrl::tft.width() - xPos;
    }
    double portSize = random(minS,maxS); 
    if (portSize < 50) portSize = 50.0;   
    double lineWidth = 1.0;//random(1,5);    
    double aspectRatio = 2.0/random(1,4);
    int color = random(0,0xFFFFFF);
    double baseSizePerc = double(random(0,90))/100.0;
    double connectorSize = double(random(5,90));
    SCtrl::tft.fillRect(0,0,480,320,TFT_BLACK);
    AndGate* andGate = new AndGate(
      xPos,
      yPos,
      portSize,
      connectors,
      vertical,
      color,
      lineWidth,
      aspectRatio,
      baseSizePerc,
      connectorSize
    );
    andGate->draw();
    delete andGate;
    andGate = nullptr;
    delay(1000);
  }
};


void ScreenPort::draw(char* params[]){
    /*SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
    SCtrl::tft.setTextColor(TFT_WHITE);
    SCtrl::tft.setTextSize(2);
    SCtrl::tft.setCursor(10, 10);
    TextInfo ti = SCtrl::drawCenteredText("MODO TUTORIAL");
    this->drawBackButton();
    SCtrl::tft.drawRect(5, ti.h+10, SCtrl::tft.width() - 10, SCtrl::tft.height() - (ti.h+10), TFT_WHITE);
    ti = SCtrl::drawCenteredText("Porta AND",ti.h+20);
    if (params != nullptr) {
      if (params[0] == "AND") {
        drawRandomAndPort();
      } else if (params[0] == "OR") {
        drawRandomOrPort();
      }
    }*/
  };
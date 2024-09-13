//#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage
#include "EVRcpt.h"
#include "SCtrl.h"
#include "Screens.h"
#include "ScreenInitialMenu.h"
#include "ScreenPort.h"
#include "ScreenLearning.h"

bool inClick = false; //AVOID LOOP ON DISPATH MULTIPLE CLICKS AT SOME TIME


void setup(){
  Serial.begin(9600);
  SCtrl::init();  
  //Serial.print(SCtrl::TS_XP);
  //Screens::goTo(ScreenInitialMenu::SCREEN_ID);
  Screens::goTo(ScreenLearning::SCREEN_ID);
  /*char* params[] = {"AND",nullptr};
  Screens::goTo(ScreenPort::SCREEN_ID,params);*/
  /*SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
  SCtrl::tft.setTextColor(TFT_WHITE);
  SCtrl::drawArcFromArrow(50, 100, 300, 150, 60);*/
};

void loop() {

  //get clicked point (if cliqued, z > 0, z = pressure)
  TSPoint p = SCtrl::ts.getPoint();

  //stackoverflow credits: restore status of shared pins to avoid not responding tft call functions
  pinMode(SCtrl::TS_XM,OUTPUT);
  pinMode(SCtrl::TS_YP,OUTPUT);

  //clicked
  if (p.z > 0 && !inClick) {
    inClick = true;
    //Serial.println("xps "+String(SCtrl::TS_XP)+" " + String(SCtrl::TS_YP) + " " + String(SCtrl::TS_XM) + " " + String(SCtrl::TS_YM));    
    DPoint uiP;
    int16_t px2 = p.x;
    int16_t py2 = p.y;
    uiP.x = map(p.y, SCtrl::TS_MINY, SCtrl::TS_MAXY, SCtrl::tft.width(),0);
    uiP.y = map(px2, SCtrl::TS_MINX, SCtrl::TS_MAXX, SCtrl::tft.height(),0);
    Serial.println("clicked on " + String(px2) + "," + String(py2) + " " +String(uiP.x) + "," + String(uiP.y) + " " + String(inClick));

    //loop troght event receptors array, checking if is point in area of element
    EVRcpt* EVRcptTemp = lastEVRcpt;
    while(EVRcptTemp != nullptr) {
      if (EVRcptTemp->checkClickEvent(uiP) == true) {
        break;//not bubble event
      }
      EVRcptTemp = EVRcptTemp->prev;
    }
    inClick = false;
  }  
  //FREERAM_PRINT; //show free memory
  delay(100); //to preserve resources, disable in production
};

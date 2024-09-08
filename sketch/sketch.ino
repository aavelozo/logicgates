#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage
#include "EventReceptor.h";
#include "TSController.h";
#include "Screens.h";



void setup(){
  Serial.begin(9600);

  TSController::init();  
  Serial.print(TSController::TS_XP);
  Screens::get("initial")->draw();
  /*delay(1000);
  ScreenLearning::draw();*/
};

bool inClick = false;
void loop() {
  TSPoint p = TSController::ts.getPoint();

  //stackoverflow: restore status of shared pins to avoid not responding tft call functions
  pinMode(TSController::TS_XM,OUTPUT);
  pinMode(TSController::TS_YP,OUTPUT);

  if (p.z > 0 && !inClick) {
    inClick = true;
    Serial.println("xps "+String(TSController::TS_XP)+" " + String(TSController::TS_YP) + " " + String(TSController::TS_XM) + " " + String(TSController::TS_YM));    
    UIPoint uiP;
    int px2 = p.x;
    int py2 = p.y;
    uiP.x = map(p.y, TSController::TS_MINY, TSController::TS_MAXY, TSController::tft.width(),0);
    uiP.y = map(px2, TSController::TS_MINX, TSController::TS_MAXX, TSController::tft.height(),0);
    Serial.println("clicked on " + String(px2) + "," + String(py2) + " " +String(uiP.x) + "," + String(uiP.y) + " " + String(inClick));

    EventReceptor* eventReceptorTemp = lastEventReceptor;
    while(eventReceptorTemp != nullptr) {
      if (eventReceptorTemp->checkClickEvent(uiP) == true) {
        break;//not bubble event
      }
      eventReceptorTemp = eventReceptorTemp->prev;
    }
    inClick = false;
  }  
  //FREERAM_PRINT;
  delay(100);
};

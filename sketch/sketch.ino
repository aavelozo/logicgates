#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage
#include "EventReceptor.h";
#include "TSController.h";
#include "Screens.h";
#include "ScreenInitialMenu.h";
#include "ScreenPort.h";

bool inClick = false; //AVOID LOOP ON DISPATH MULTIPLE CLICKS AT SOME TIME


void setup(){
  Serial.begin(9600);
  TSController::init();  
  Serial.print(TSController::TS_XP);
  //Screens::goTo(ScreenInitialMenu::SCREEN_ID);
  Screens::goTo(ScreenPort::SCREEN_ID);
};

void loop() {

  //get clicked point (if cliqued, z > 0, z = pressure)
  TSPoint p = TSController::ts.getPoint();

  //stackoverflow credits: restore status of shared pins to avoid not responding tft call functions
  pinMode(TSController::TS_XM,OUTPUT);
  pinMode(TSController::TS_YP,OUTPUT);

  //clicked
  if (p.z > 0 && !inClick) {
    inClick = true;
    Serial.println("xps "+String(TSController::TS_XP)+" " + String(TSController::TS_YP) + " " + String(TSController::TS_XM) + " " + String(TSController::TS_YM));    
    UIPoint uiP;
    int16_t px2 = p.x;
    int16_t py2 = p.y;
    uiP.x = map(p.y, TSController::TS_MINY, TSController::TS_MAXY, TSController::tft.width(),0);
    uiP.y = map(px2, TSController::TS_MINX, TSController::TS_MAXX, TSController::tft.height(),0);
    Serial.println("clicked on " + String(px2) + "," + String(py2) + " " +String(uiP.x) + "," + String(uiP.y) + " " + String(inClick));

    //loop troght event receptors array, checking if is point in area of element
    EventReceptor* eventReceptorTemp = lastEventReceptor;
    while(eventReceptorTemp != nullptr) {
      if (eventReceptorTemp->checkClickEvent(uiP) == true) {
        break;//not bubble event
      }
      eventReceptorTemp = eventReceptorTemp->prev;
    }
    inClick = false;
  }  
  //FREERAM_PRINT; //show free memory
  delay(100); //to preserve resources, disable in production
};

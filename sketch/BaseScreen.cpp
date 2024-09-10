#include "BaseScreen.h";
#include "TSController.h";
#include "EventReceptor.h";
#include "Screens.h";

//back button
void BaseScreen::drawBackButton(){
  int px = 5;
  int py = 2;
  int size = 22;
  TSController::tft.fillRoundRect(px,py,size,size,3,TFT_DARKGREY);
  TSController::drawCenteredText("<",py+5, px+((size-px)/2));
  EventReceptor* ev = new EventReceptor(0,py+5,size/1.5);
  ev->onClick = [](){
    Serial.print("IN ON CLICK OF BASE SCREEN (BACK BUTTON) ");
    clearAllEventReceptors();
    Screens::goBack();    
  };
}



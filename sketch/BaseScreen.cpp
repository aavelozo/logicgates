#include "BaseScreen.h";
#include "TSController.h";
#include "EventReceptor.h";
#include "Screens.h";

void BaseScreen::drawBackButton(BaseScreen* screen){
  int px = 5;
  int py = 2;
  int size = 22;
  TSController::tft.fillRoundRect(px,py,size,size,3,TFT_DARKGREY);
  TSController::drawCenteredText("<",py+5, px+((size-px)/2));
  EventReceptor* ev = new EventReceptor(0,py+5,size/1.5);
  Screens::currentScreen = Screens::get("initial");
  ev->onClick = [](){
    clearAllEventReceptors();
    Screens::currentScreen->draw();    
  };
}

void BaseScreen::draw(){
  Screens::currentScreen = this;
}


#include "ScreenInitialMenu.h";
#include "Utils.h";
#include "TSController.h";
#include "EventReceptor.h";
#include "ScreenLearning.h";
#include "Screens.h";

//draw menus items inciais
void ScreenInitialMenu::drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção"){
  TSController::tft.drawCircle(itemMenuXPos,itemMenuYPos,itemR,colorExtern);
  TSController::tft.drawCircle(itemMenuXPos,itemMenuYPos,itemR-1,colorExtern);
  TSController::tft.fillCircle(itemMenuXPos,itemMenuYPos,itemR*0.8,colorExtern);
  int playColor = TFT_BLACK;
  float playR = itemR * 0.25;
  float arred = itemR * 0.05;

  //define os pontos do triangulo do play
  FPoint p1,p2,p3;
  p1.x = p2.x = (itemMenuXPos - playR) + (itemR * 0.1);
  p1.y = itemMenuYPos - playR;
  p2.y = itemMenuYPos + playR;
  p3.x = itemMenuXPos + playR + (itemR * 0.1);
  p3.y = itemMenuYPos;

  //desenha o play
  TSController::tft.fillTriangle(p1.x,p1.y, p2.x,p2.y, p3.x,p3.y , playColor);

  //desenha os cantos arredondados
  TSController::tft.fillCircle(p1.x,p1.y,arred*2, colorExtern);
  TSController::tft.fillCircle(p1.x+arred*0.8,p1.y+arred*1.75,arred, playColor);
  TSController::tft.fillCircle(p2.x,p2.y,arred*2, colorExtern);
  TSController::tft.fillCircle(p2.x+arred*0.8,p2.y-arred*1.55,arred, playColor);
  TSController::tft.fillCircle(p3.x,p3.y,arred*2, colorExtern);
  TSController::tft.fillCircle(p3.x-arred*2.3,p3.y,arred, playColor);
  TSController::drawCenteredText(text,itemMenuYPos+itemR+20,p1.x);
};

void ScreenInitialMenu::draw() {
  Serial.println("INIT ScreenInitialMenu::draw");
  TSController::tft.fillScreen(TFT_BLACK);  // Limpa a tela
  TSController::tft.setTextColor(TFT_WHITE);
  TSController::tft.setTextSize(2);
  TSController::tft.setCursor(10, 10);
  TextInfo ti = TSController::drawCenteredText("PORTAS E CIRCUITOS");
  TSController::tft.drawRect(5, ti.h+10, TSController::tft.width() - 10, TSController::tft.height() - (ti.h+10), TFT_WHITE);
  ti = TSController::drawCenteredText("Modos de jogo",ti.h+20);
  float _4Div = TSController::tft.width() / 4;
  float itemMenuXPos = _4Div / 2;
  float itemMenuYPos = TSController::tft.height() / 2;
  float itemR = itemMenuXPos * 0.6;
  drawMenuItem(itemMenuXPos, itemMenuYPos,itemR,TFT_YELLOW,"Aprenda");
  drawMenuItem(itemMenuXPos + _4Div, itemMenuYPos,itemR,TFT_BLUE,"Pontuacao");
  drawMenuItem(itemMenuXPos + _4Div * 2, itemMenuYPos,itemR,TFT_GREEN,"Tempo");
  drawMenuItem(itemMenuXPos + _4Div * 3, itemMenuYPos,itemR,TFT_RED,"Construa");  

  EventReceptor* ev = new EventReceptor(itemMenuXPos,itemMenuYPos,itemR);
  ev->onClick = [](){
    Serial.println("IN ON CLICK OF INITIAL SCREEN (LEARNING)");
    clearAllEventReceptors();
    Screens::goTo(ScreenLearning::SCREEN_ID);
  };
  Serial.println("END ScreenInitialMenu::draw");
};
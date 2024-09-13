#include "ScreenLearning.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenPort.h"
#include "AndGate.h"

void ScreenLearning::draw(char* params[]){
  Serial.println("INIT ScreenLearning::draw");
  Serial.println("ILD");
  SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
  SCtrl::tft.setTextColor(TFT_WHITE);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setCursor(10, 10);
  TextInfo ti = SCtrl::drawCenteredText("MODO APRENDER");
  this->drawBackButton();
  SCtrl::tft.drawRect(5, ti.h+10, SCtrl::tft.width() - 10, SCtrl::tft.height() - (ti.h+10), TFT_WHITE);
  //ti = SCtrl::drawCenteredText("Escolha uma porta",ti.h+20);

  int cols = 3;
  int lins = 2;
  double x = SCtrl::tft.width() * 1.0 / cols;
  x = x / 2.0;
  double y = (SCtrl::tft.height() * 1.0 - ti.y) / lins;
  y = y / 2.0;
  double r = x;
  if (y < x) {
    r = y;
  }
  r = r * 0.6;
  int col = 0;
  int lin = 0;


/*#define ROSA_CLARO 0xFFB6C1
#define AZUL_CLARO 0xADD8E6
#define VERDE_CLARO 0x90EE90
#define AMARELO_CLARO 0xFFFFE0
#define LILAS_CLARO 0xE6E6FA
#define PESSSEGO_CLARO 0xFFDAB9*/

  SCtrl::drawRoundButton(x + (col * (x*2.0)),y + (lin * (y * 2.0)),r,PESSSEGO_CLARO,"AND",false,true,10.0,[](){
    char* params[] = {"AND", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });

  AndGate* ag = new AndGate(
    x+(col*(x*2.0))-(r*0.35),
    y+(lin*(y*2.0))+(r*0.35),
    r*0.7,
    DEFAULT_GATE_CONNECTOR_COUNT,
    DEFAULT_GATE_VERTICAL_DIRECTION,
    TFT_BLACK,//DEFAULT_GATE_LINE_COLOR,
    1,//DEFAULT_GATE_LINE_WIDTH,
    1,//DEFAULT_GATE_ASPECT_RATIO,
    DEFAULT_GATE_BASE_SIZE_PERC
  );
  ag->draw();

  /*col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + (lin * (y * 2)),r,TFT_GREEN,"OR",false,true,10,[](){
    char* params[] = {"OR", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });
  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + (lin * (y * 2)),r,TFT_RED,"NOT",false,true,10,[](){
    char* params[] = {"NOT", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });
  col = 0;
  lin++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + (lin * (y * 2)),r,TFT_YELLOW,"NAND",false,true,10,[](){
    char* params[] = {"NAND", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });
  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + (lin * (y * 2)),r,TFT_CYAN,"NOR",false,true,10,[](){
    char* params[] = {"NOR", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });
  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + (lin * (y * 2)),r,TFT_MAGENTA,"XOR",false,true,10,[](){
    char* params[] = {"XOR", nullptr};
    Screens::goTo(ScreenPort::SCREEN_ID,params);
  });*/

};
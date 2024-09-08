#include "ScreenLearning.h";
#include "Utils.h";
#include "TSController.h";
#include "EventReceptor.h";
#include "Screens.h";
#include "EventReceptor.h";

#define BUTTON_WIDTH  120
#define BUTTON_HEIGHT 60
#define BUTTON_SPACING 20

#define COLUMN1_X_START  TSController::tft.width() / 2 - (BUTTON_WIDTH + (BUTTON_SPACING))
#define COLUMN2_X_START  (COLUMN1_X_START + BUTTON_WIDTH + 2 * BUTTON_SPACING)
#define BUTTON_Y_START   75

static void ScreenLearning::drawMenuItem(float itemMenuXPos,float itemMenuYPos,float itemR,int colorExtern,const char* text = "Opção"){
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

void drawButton(int x, int y, const char* label, uint16_t color) {
  int r = 5;
  TSController::tft.fillRoundRect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, r, color);         // Botão preenchido
  TSController::tft.drawRoundRect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, r, TFT_WHITE);         // Borda do botão
  TSController::tft.setTextColor(TFT_BLACK);                                       // Cor do texto
  TSController::drawCenteredText(label,y+BUTTON_HEIGHT/2.2,x+BUTTON_WIDTH/2);
}

void ScreenLearning::draw(){
    Serial.println("ILD");
    BaseScreen::draw();
    TSController::tft.fillScreen(TFT_BLACK);  // Limpa a tela
    TSController::tft.setTextColor(TFT_WHITE);
    TSController::tft.setTextSize(2);
    TSController::tft.setCursor(10, 10);
    TextInfo ti = TSController::drawCenteredText("MODO APRENDER");
    this->drawBackButton(Screens::get("initial"));
    TSController::tft.drawRect(5, ti.h+10, TSController::tft.width() - 10, TSController::tft.height() - (ti.h+10), TFT_WHITE);
    ti = TSController::drawCenteredText("Escolha uma porta",ti.h+20);
    float _4Div = TSController::tft.width() / 4;
    float itemMenuXPos = _4Div / 2;
    float itemMenuYPos = TSController::tft.height() / 2;
    float itemR = itemMenuXPos * 0.6;
    drawButton(COLUMN1_X_START, BUTTON_Y_START, "AND", TFT_RED);
    drawButton(COLUMN1_X_START, BUTTON_Y_START + BUTTON_HEIGHT + BUTTON_SPACING, "OR", TFT_GREEN);
    drawButton(COLUMN1_X_START, BUTTON_Y_START + 2 * (BUTTON_HEIGHT + BUTTON_SPACING), "NOT", TFT_BLUE);
    drawButton(COLUMN2_X_START, BUTTON_Y_START, "NAND", TFT_YELLOW);
    drawButton(COLUMN2_X_START, BUTTON_Y_START + BUTTON_HEIGHT + BUTTON_SPACING, "NOR", TFT_CYAN);
    drawButton(COLUMN2_X_START, BUTTON_Y_START + 2 * (BUTTON_HEIGHT + BUTTON_SPACING), "XOR", TFT_MAGENTA);

    EventReceptor* ev = new EventReceptor(COLUMN1_X_START + BUTTON_WIDTH / 2,BUTTON_Y_START + BUTTON_HEIGHT / 2,BUTTON_WIDTH / 2);
    ev->onClick = [](){
      Serial.println("clicked in button");
    };
    Serial.println("ELD");
  };
#include "TSController.h";
#include <TouchScreen.h>   // Biblioteca para touchscreen

TouchScreen TSController::ts = TouchScreen(TSController::TS_XP, TSController::TS_YP, TSController::TS_XM, TSController::TS_YM, 300);
MCUFRIEND_kbv TSController::tft;// = MCUFRIEND_kbv();
static void TSController::init(){
    // Configuração do touchscreen
    // Inicializa o TFT
    uint16_t identifier = tft.readID();
    Serial.println("TFT SHIELD IDENTIFIER: "+String(identifier));
    if (identifier == 0x9325 || identifier == 0x9341 || identifier == 0x9486 || identifier == 0x7796) {
      tft.begin(identifier);
    } else {
      tft.begin(0x9486);  // Força o uso de um controlador comum, se necessário
    }
    tft.setRotation(1);  // Ajuste a rotação conforme necessário
};

static TextInfo TSController::drawCenteredText(const char* text, int y = 0, float centerX = TSController::tft.width() / 2, int textSize = 2, int color = TFT_WHITE) {
  // Defina o tamanho do texto
  TextInfo result;
  TSController::tft.setTextSize(textSize);
  
  // Calcule a largura do texto
 //int x1, y1;  // Variáveis para armazenar a posição do canto superior esquerdo
  //int w, h;   // Largura e altura do texto

  TSController::tft.getTextBounds(text, 0, y, &result.x, &result.y, &result.w, &result.h);  // Calcula as dimensões do texto
  
  // Calcule a posição X centralizada
  int x = centerX - (result.w / 2);
  
  // Desenhe o texto na posição centralizada
  TSController::tft.setCursor(x, y);
  TSController::tft.setTextColor(color);
  TSController::tft.print(text);
  return result;
};


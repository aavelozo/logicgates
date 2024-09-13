#include "SCtrl.h"
#include <TouchScreen.h>   // Biblioteca para touchscreen
#include "Utils.h"
#include "EVRcpt.h"
#include <math.h>

TouchScreen SCtrl::ts = TouchScreen(SCtrl::TS_XP, SCtrl::TS_YP, SCtrl::TS_XM, SCtrl::TS_YM, 300);
MCUFRIEND_kbv SCtrl::tft;



void SCtrl::init(){
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

TextInfo SCtrl::drawCenteredText(const char* text, double y, double centerX, double textSize, int color) {
    // Defina o tamanho da fonte
    SCtrl::tft.setTextSize(textSize);
    SCtrl::tft.setTextColor(color);

    // Calcule a largura e altura do texto com base no tamanho da fonte
    double textWidth = strlen(text) * 6.0 * textSize;  // Cada caractere tem aproximadamente 6px de largura na fonte padrão
    double textHeight = 8.0 * textSize;  // A altura da fonte padrão é de aproximadamente 8px

    // Calcule as coordenadas para centralizar o texto
    double x = centerX - (textWidth / 2.0);
    
    // Desenhe o texto no TFT
    SCtrl::tft.setCursor(x, y);
    SCtrl::tft.print(text);

    // Retorne as informações do texto
    TextInfo result;
    result.x = x;
    result.y = y;
    result.w = textWidth;
    result.h = textHeight;
    return result;
};

static void SCtrl::drawSmoothArc(double x_center, double y_center, double radius, double start_angle, double end_angle, uint16_t color) {
    double angle;   // Ângulo atual em radianos
    double x_last = -1.0, y_last = -1.0;  // Últimas coordenadas desenhadas para garantir continuidade

    // Convertendo ângulos de graus para radianos
    double start_rad = start_angle * (PI / 180.0);
    double end_rad = end_angle * (PI / 180.0);

    // Caminhar ao longo do arco, aumentando o ângulo gradualmente
    for (angle = start_rad; angle <= end_rad; angle += 0.005) {
        double x = x_center + radius * cos(angle);  // Cálculo da coordenada X
        double y = y_center + radius * sin(angle);  // Cálculo da coordenada Y
        //SCtrl::tft.drawPixel(x, y, color);
        // Desenha o pixel apenas se for uma nova coordenada (evitar sobreposição)
        if (x != x_last || y != y_last) {
            SCtrl::tft.drawPixel(x, y, color);  // Desenha o pixel na posição (x, y)
            x_last = x;
            y_last = y;
        }
    }
};

static void SCtrl::drawRoundButton(double x,double y,double r,int color,const char* text, bool hasCenterPlay, bool hasBorder, double textDistance = 20, void (*onClick)()) {
  if (hasBorder) {
    SCtrl::tft.drawCircle(x,y,r,color);
    SCtrl::tft.drawCircle(x,y,r-1.0,color);
    SCtrl::tft.fillCircle(x,y,r*0.8,color);
  } else {
    SCtrl::tft.fillCircle(x,y,r,color);
  }

  DPoint p1;
  double playR = r * 0.20;
  p1.x = (x - playR) + (r * 0.1);
  if (hasCenterPlay) {
    int playColor = TFT_BLACK;    
    double arred = r * 0.00;

    //define os pontos do triangulo do play
    DPoint p2,p3;    
    p1.y = y - playR;
    p2.x = p1.x;
    p2.y = y + playR;
    p3.x = x + playR + (r * 0.1);
    p3.y = y;

    //desenha o play
    SCtrl::tft.fillTriangle(p1.x,p1.y, p2.x,p2.y, p3.x,p3.y , playColor);

    //desenha os cantos arredondados
    SCtrl::tft.fillCircle(p1.x,p1.y,arred*2.0, color);
    SCtrl::tft.fillCircle(p1.x+arred*0.8,p1.y+arred*1.70,arred, playColor);
    SCtrl::tft.fillCircle(p2.x,p2.y,arred*2.0, color);
    SCtrl::tft.fillCircle(p2.x+arred*0.8,p2.y-arred*1.50,arred, playColor);
    SCtrl::tft.fillCircle(p3.x,p3.y,arred*2.0, color);
    SCtrl::tft.fillCircle(p3.x-arred*2.3,p3.y,arred, playColor);
  }
  if (text != "") {
    SCtrl::drawCenteredText(text,y+r+textDistance,p1.x);
  }
  if (onClick != nullptr) {
    new EVRcpt(x, y, r, onClick);
  }
};




// Função para desenhar o arco
static void SCtrl::drawArcFromArrow(double x1, double y1, double x2, double y2, double arcHeight, int color) {  
  DPoint p1,p2;
  p1.x = x1;
  p1.y = y1;
  p2.x = x2;
  p2.y = y2;

  double width = sqrt(pow(abs(x2-x1),2.0) + pow(abs(y2-y1),2.0));
  double r = 0.0;
  double baseAdjust = 0.0;
  double centralAngle = 270.0; //arco na horizontal, flexa na vertical y1 = y2 --- 
  if (y1 != y2) {
    if (x1 == x2) {// arco na vertical, flexa na horizontal |      
      centralAngle = 0.0;
      if (y1 > y2) {
        centralAngle = 180.0; //arco na vertical, flexa na horizontal, apontando para a esquerda
      }
    } else {
      double hT = abs(y1-y2); //cateto vertical
      double wT = abs(x1-x2); //cateto horizontal
      double a1 = atan(hT/wT) * (180.0 / M_PI); //angulo oposto ao cateto vertical
      if (x1 < x2) { //flexa/arco para direita
        centralAngle = 180.0-(a1+90.0); // /-
        if (y1 < y2) {//flexa/arco para cima ou 1º quadrante (x+,y+) sent horario  \-
          centralAngle = 360.0 - centralAngle;
        } 
      } else {//flexa do arco para esquerda
        centralAngle = 180.0-(a1+90.0)+180.0; // -/
        if (y1 < y2) {//flexa/arco para cima ou 3º quadrante (x-,y+) sent horario -/
          centralAngle = centralAngle - 90.0; // \-
        }
      }
    }
  } else if (x1 > x2) {
    centralAngle = 90.0; //flexa apontando para baixo
  }
  if (arcHeight >= width/2.0) {
    r = width / 2.0;
    baseAdjust = arcHeight - r;
  } else {
    r = (arcHeight * arcHeight + pow(width/2.0,2.0)) / (2.0 * arcHeight);
  }
  double py2 = pow(r,2.0);
  py2 = pow(r,2) - pow(width /2.0,2.0);
  py2 = sqrt(py2);
  double arcAngle = getArcAngle(width,r);
  double startAngle = centralAngle-(arcAngle/2.0)+0.0;

  DPoint pc = calcularP3(width,r,r,p1,p2);

  SCtrl::drawSmoothArc(pc.x,pc.y,r,startAngle,startAngle+arcAngle+0.0,color);    
}



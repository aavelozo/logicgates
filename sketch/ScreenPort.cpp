#include "ScreenPort.h";
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
#define DEFAULT_PORT_SIZE 150
#define DEFAULT_PORT_ASPECT_RATIO 0.5
#define DEFAULT_PORT_LINE_COLOR TFT_WHITE
#define DEFAULT_PORT_CONNECTOR_LENGTH_PERC 0.3
#define DEFAULT_PORT_VERTICAL_DIRECTION true
#define DEFAULT_PORT_CONNECTOR_MARGIN_PERC 0.1
#define DEFAULT_PORT_LINE_WIDTH 3



void drawPortConnector(
  int baseXPort, 
  int baseYPort,
  byte position,
  byte totalConnectors = 2,
  int portSize = DEFAULT_PORT_SIZE, 
  int connectorLength = DEFAULT_PORT_SIZE * DEFAULT_PORT_CONNECTOR_LENGTH_PERC,
  bool vertical = DEFAULT_PORT_VERTICAL_DIRECTION, 
  int color = DEFAULT_PORT_LINE_COLOR,
  float aspectRatio = DEFAULT_PORT_ASPECT_RATIO  
) { 
  int portLarg = portSize * aspectRatio;
  int portConnMargem = portLarg * DEFAULT_PORT_CONNECTOR_MARGIN_PERC;
  if (position > 0) {        
    portConnMargem = portConnMargem + (position * (portLarg - (portConnMargem * 2)) / (totalConnectors - 1));
  } 
  if (vertical) {
    TSController::tft.drawLine(baseXPort + portConnMargem,baseYPort,baseXPort + portConnMargem,baseYPort + connectorLength, color);
  } else {
    TSController::tft.drawLine(baseXPort, baseYPort + portConnMargem,baseXPort - connectorLength,baseYPort + portConnMargem, color);
  }
}

void drawPortOutputConnector(
  int baseXPort, 
  int baseYPort,
  byte position,
  byte totalConnectors = 2,
  int portSize = DEFAULT_PORT_SIZE, 
  int connectorLength = DEFAULT_PORT_SIZE * DEFAULT_PORT_CONNECTOR_LENGTH_PERC,
  bool vertical = DEFAULT_PORT_VERTICAL_DIRECTION, 
  int color = DEFAULT_PORT_LINE_COLOR,
  float aspectRatio = DEFAULT_PORT_ASPECT_RATIO  
) { 
  int portLarg = portSize * aspectRatio;
  int portConnMargem = portLarg * DEFAULT_PORT_CONNECTOR_MARGIN_PERC;
  if (position > 0) {        
    portConnMargem = portConnMargem + (position * (portLarg - (portConnMargem * 2)) / (totalConnectors - 1));
  } 
  if (vertical) {
    TSController::tft.drawLine(baseXPort + (portLarg / 2 ) ,baseYPort - portSize - connectorLength,baseXPort + (portLarg / 2 ),baseYPort - portSize , color);
  } else {
    TSController::tft.drawLine(baseXPort + portSize ,baseYPort + (portLarg/2),baseXPort + portSize + connectorLength,baseYPort + (portLarg/2), color);
  }
}


/*void drawPieSlice(int x, int y, int radius, int color, int startAngle, int EndAngle)
{
  for (int i=startAngle; i<EndAngle; i++)
  {
    double radians = i * PI / 180;
    double px = x + radius * cos(radians);
    double py = y + radius * sin(radians);
    drawPixel(px, py, color);
  }
}*/

void desenharArco(int x0, int y0, int raio, int anguloInicio, int anguloFim, uint16_t cor) {
    // Percorre os ângulos entre anguloInicio e anguloFim
    for (int angulo = anguloInicio; angulo <= anguloFim; angulo++) {
        // Converte o ângulo de graus para radianos
        float radiano = angulo * (PI / 180.0);

        // Calcula a posição x e y do ponto na circunferência
        int x = x0 + raio * cos(radiano);
        int y = y0 + raio * sin(radiano);

        // Desenha o pixel no ponto calculado
        TSController::tft.drawPixel(x, y, cor);
    }
}

// Função para desenhar um arco sem gaps
void drawSmoothArc(int x_center, int y_center, int radius, int start_angle, int end_angle, uint16_t color) {
    float angle;   // Ângulo atual em radianos
    int x_last = -1, y_last = -1;  // Últimas coordenadas desenhadas para garantir continuidade

    // Convertendo ângulos de graus para radianos
    float start_rad = start_angle * (PI / 180.0);
    float end_rad = end_angle * (PI / 180.0);

    // Caminhar ao longo do arco, aumentando o ângulo gradualmente
    for (angle = start_rad; angle <= end_rad; angle += 0.005) {
        int x = x_center + radius * cos(angle);  // Cálculo da coordenada X
        int y = y_center + radius * sin(angle);  // Cálculo da coordenada Y
        //TSController::tft.drawPixel(x, y, color);
        // Desenha o pixel apenas se for uma nova coordenada (evitar sobreposição)
        if (x != x_last || y != y_last) {
            TSController::tft.drawPixel(x, y, color);  // Desenha o pixel na posição (x, y)
            x_last = x;
            y_last = y;
        }
    }
}

static void drawAndBody(
  int baseXPort, 
  int baseYPort, 
  byte totalConnectors = 2,
  int portSize = DEFAULT_PORT_SIZE,
  bool vertical = DEFAULT_PORT_VERTICAL_DIRECTION, 
  int color = DEFAULT_PORT_LINE_COLOR,
  float aspectRatio = DEFAULT_PORT_ASPECT_RATIO,  
  byte lineWidth = DEFAULT_PORT_LINE_WIDTH
) {
  float portLarg = portSize * aspectRatio;
  float arcHeightPerc = 1.0/totalConnectors;
  //Serial.println("arcHeightPerc " + String(arcHeightPerc));
  if (arcHeightPerc < 0.2) {
    arcHeightPerc = 0.2;
  }
  //Serial.println("arcHeightPerc " + String(arcHeightPerc));
  float arcHeight = portSize * arcHeightPerc;
  //Serial.println("arcHeight " + String(arcHeight));

  //R=C^2/8*h + h/2 formula raio com base em semiarco e linha tocando dois pontos
  float r = (arcHeight * arcHeight + pow(portLarg/2,2)) / (2 * arcHeight);
  //Serial.println("archeight"+String(arcHeight) + " portlarg " + String(portLarg) + " r " + String(r));
  float py2 = pow(r,2);
  //Serial.println("py2 " + String(py2));
  py2 = pow(r,2) - pow(portLarg /2,2);
  //Serial.println("py2 " + String(py2));
  py2 = sqrt(py2);
  //Serial.println("py2 " + String(py2));
  float arcAngle = getArcAngle(portLarg,r);
  //Serial.println("arc angle " + String(arcAngle));
  
  if (vertical) {
    TSController::tft.fillRect(baseXPort,baseYPort-lineWidth,portLarg,lineWidth,color); //base line
    TSController::tft.fillRect(baseXPort,baseYPort-portSize+arcHeight,lineWidth,portSize-arcHeight,color); //left line
    TSController::tft.fillRect(baseXPort+portLarg-lineWidth,baseYPort-portSize+arcHeight,lineWidth,portSize-arcHeight,color); //rigth line        
    py2 = baseYPort - portSize + arcHeight + py2;
    //Serial.println("py2 " + String(py2));    
    float startAngle = 270-(arcAngle/2)+0.5;
    drawSmoothArc(baseXPort+(portLarg/2),py2,r,startAngle,startAngle+arcAngle+0.5,color);
    
  } else {
    TSController::tft.fillRect(baseXPort,baseYPort,lineWidth,portLarg,color);
    TSController::tft.fillRect(baseXPort,baseYPort,portSize-arcHeight,lineWidth,color); //left line
    TSController::tft.fillRect(baseXPort,baseYPort+portLarg,portSize-arcHeight,lineWidth,color); //rigth line

    py2 = baseXPort + (portSize - arcHeight) - py2;
    //Serial.println("py2 " + String(py2));    
    float startAngle = 0-(arcAngle/2)+0.5;
    drawSmoothArc(py2,baseYPort+(portLarg/2),r,startAngle,startAngle+arcAngle+0.5,color);

  }
}

static void drawPortBody(
  byte portId,
  int baseXPort, 
  int baseYPort, 
  byte totalConnectors = 2,
  int portSize = DEFAULT_PORT_SIZE,
  bool vertical = DEFAULT_PORT_VERTICAL_DIRECTION, 
  int color = DEFAULT_PORT_LINE_COLOR,
  float aspectRatio = DEFAULT_PORT_ASPECT_RATIO,
  byte lineWidth = DEFAULT_PORT_LINE_WIDTH  
){
  switch(portId) {
    case 0:
      drawAndBody(baseXPort,baseYPort,totalConnectors,portSize,vertical,color,aspectRatio,lineWidth);
      break;
  }
}

static drawPort(
  byte portId, 
  int baseXPort, 
  int baseYPort,
  byte totalConnectors = 2,
  int portSize = DEFAULT_PORT_SIZE,    
  int connectorLength = DEFAULT_PORT_SIZE * DEFAULT_PORT_CONNECTOR_LENGTH_PERC,
  bool vertical = DEFAULT_PORT_VERTICAL_DIRECTION, 
  int color = DEFAULT_PORT_LINE_COLOR,
  float aspectRatio = DEFAULT_PORT_ASPECT_RATIO,
  byte lineWidth = DEFAULT_PORT_LINE_WIDTH  
){
  //int portSize = 250;
  for(byte i = 0; i < totalConnectors; i++) {
    drawPortConnector(baseXPort,baseYPort,i,totalConnectors,portSize,connectorLength,vertical,color,aspectRatio);
  }
  drawPortOutputConnector(baseXPort,baseYPort,0,totalConnectors,portSize,connectorLength,vertical,color,aspectRatio);
  drawPortBody(portId,baseXPort,baseYPort,totalConnectors,portSize,vertical,color,aspectRatio,lineWidth);
};

void drawRandomAndPort(){
  int minX = 0;
  int maxX = TSController::tft.width() * 0.8;
  int minY = 0;
  int maxY = TSController::tft.height(); 
  int minS = 50;
  int maxS = TSController::tft.width() * 0.8;
  for (int i = 0; i < 100; i++) {
    bool vertical = random(0, 2) == 1;
    maxX = TSController::tft.width() * 0.8;
    if (vertical) {
      minY = 100;
    } else {
      minY = 0;
      maxX = TSController::tft.width() * 0.65;
    }
    int xPos = random(minX,maxX);
    int yPos = random(minY,maxY);
    byte connectors = random(2,8);
    if (vertical) {
      maxS = TSController::tft.height() - yPos;
    } else {
      maxS = TSController::tft.width() - xPos;
    }
    int portSize = random(minS,maxS); 
    if (portSize < 50) portSize = 50;   
    byte lineWidth = 1;//random(1,5);    
    float aspectRatio = 2/random(1,3);
    int color = random(0,0xFFFFFF);
    TSController::tft.fillRect(0,0,480,320,TFT_BLACK);
    drawPort(
      0,
      xPos,
      yPos,
      connectors,
      portSize,
      portSize*DEFAULT_PORT_CONNECTOR_LENGTH_PERC,
      vertical,
      color,
      aspectRatio,
      lineWidth
    );
    delay(1000);
  }
  //Screens::currentScreen->draw();
}

void ScreenPort::draw(){
    Serial.println("INIT ScreenPort::draw");
    TSController::tft.fillScreen(TFT_BLACK);  // Limpa a tela
    TSController::tft.setTextColor(TFT_WHITE);
    TSController::tft.setTextSize(2);
    TSController::tft.setCursor(10, 10);
    TextInfo ti = TSController::drawCenteredText("MODO TUTORIAL");
    this->drawBackButton();
    TSController::tft.drawRect(5, ti.h+10, TSController::tft.width() - 10, TSController::tft.height() - (ti.h+10), TFT_WHITE);
    ti = TSController::drawCenteredText("Porta AND",ti.h+20);
    //for(int i = 0; i < 100; i++) {
      drawRandomAndPort();
      
    //}

    Serial.println("END ScreenPort::draw");
  };
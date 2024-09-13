#include "Utils.h"
#include <math.h>  // Para usar funções trigonométricas como asin


double getArcAngle(double corda, double raio) {
    // Verifica se os parâmetros são válidos para evitar erros
    if (corda > 2 * raio) {
        // Retorna -1 para indicar erro, pois a corda não pode ser maior que o diâmetro
        return -1.0;
    }

    // Calcula o ângulo central em radianos
    double anguloRadianos = 2.0 * asin(corda / (2.0 * raio));

    // Converte o ângulo de radianos para graus
    double anguloGraus = anguloRadianos * 180.0 / M_PI;

    return anguloGraus;
};

// Função para calcular o ponto médio entre dois pontos
DPoint calcularPontoMedio(DPoint p1, DPoint p2) {
  DPoint pontoMedio;
  pontoMedio.x = (p1.x + p2.x) / 2;
  pontoMedio.y = (p1.y + p2.y) / 2;
  return pontoMedio;
}

// Função para calcular P3 com base nos comprimentos dos lados e nas coordenadas de P1 e P2
DPoint calcularP3(double a, double b, double c, DPoint p1, DPoint p2) {
  DPoint p3;
  
  // Encontrar o ponto médio entre P1 e P2
  DPoint pontoMedio = calcularPontoMedio(p1, p2);

  // Resolver o sistema de equações para encontrar P3
  double d = sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y, 2.0));  // Distância entre P1 e P2 (lado a)

  // Coordenadas de P3 (x3, y3)
  // Primeiro encontrar a distância entre P1 e P3, e P2 e P3
  double h = sqrt(pow(b, 2.0) - pow(d / 2.0, 2.0));  // Altura do triângulo em relação à base P1-P2

  // Calcular P3 usando simetria com o ponto médio e a altura
  // Direções ortogonais à reta P1P2
  double dx = (p2.y - p1.y) / d;
  double dy = (p2.x - p1.x) / d;

  // P3 estará em uma das duas posições possíveis: acima ou abaixo da linha P1-P2
  // Podemos escolher qualquer um dos dois (aqui assumimos uma direção acima da reta)
  p3.x = pontoMedio.x - h * dx;
  p3.y = pontoMedio.y + h * dy;

  return p3;
}
#include <math.h>  // Para usar funções trigonométricas como asin


float getArcAngle(float corda, float raio) {
    // Verifica se os parâmetros são válidos para evitar erros
    if (corda > 2 * raio) {
        // Retorna -1 para indicar erro, pois a corda não pode ser maior que o diâmetro
        return -1;
    }

    // Calcula o ângulo central em radianos
    float anguloRadianos = 2 * asin(corda / (2 * raio));

    // Converte o ângulo de radianos para graus
    float anguloGraus = anguloRadianos * 180.0 / M_PI;

    return anguloGraus;
}
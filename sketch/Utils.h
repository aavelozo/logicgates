#ifndef UTILS_H
#define UTILS_H

struct DPoint{
  double x,y;
};

struct UIPoint{
  int x,y;
};

double getArcAngle(double corda, double raio);
DPoint calcularP3(double a, double b, double c, DPoint p1, DPoint p2);

#endif // UTILS_H
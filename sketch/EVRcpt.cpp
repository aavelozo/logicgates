#include "EVRcpt.h"
#include <Arduino.h>
#include "Utils.h"

EVRcpt* lastEVRcpt = nullptr;

//constructor
EVRcpt::EVRcpt(double x,double y,double pDist, void (*pOnClick)()) {
  this->centerPoint.x = x;
  this->centerPoint.y = y;
  this->distance = pDist;
  this->onClick = pOnClick;
  this->prev = lastEVRcpt;      
  lastEVRcpt = this;
};

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool EVRcpt::checkClickEvent(DPoint point) {   
  //Serial.println("x "+String(centerPoint.x) + " y " + String(centerPoint.y) + " px " + String(point.x) + " py " + String(point.y) + " ax " + String(abs(centerPoint.x - point.x)) + " ay " + String(abs(centerPoint.y - point.y)) + " d " + String(distance));
  if (abs(centerPoint.x - point.x) <= distance && abs(centerPoint.y - point.y) <= distance) {
    //Serial.println("CLICKED ON ELEMENT (TRIGGERING EVENT)");
    onClick();
    return true;
  }
  return false;
};

void clearAllEVRcpts(){
  EVRcpt* temp = lastEVRcpt;
  while(lastEVRcpt != nullptr) {
    temp = lastEVRcpt;
    lastEVRcpt = lastEVRcpt->prev;
    delete temp;    
  }
  lastEVRcpt = nullptr;
};
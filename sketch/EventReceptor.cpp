#include "EventReceptor.h";
#include <Arduino.h>;
#include "Utils.h";

EventReceptor* lastEventReceptor = nullptr;

EventReceptor::EventReceptor(int x,int y,int pDist) {
  this->centerPoint.x = x;
  this->centerPoint.y = y;
  this->distance = pDist;
  this->prev = lastEventReceptor;      
  lastEventReceptor = this;
};

bool EventReceptor::checkClickEvent(UIPoint point) {   
  Serial.println("x "+String(centerPoint.x) + " y " + String(centerPoint.y) + " px " + String(point.x) + " py " + String(point.y) + " ax " + String(abs(centerPoint.x - point.x)) + " ay " + String(abs(centerPoint.y - point.y)) + " d " + String(distance));
  if (abs(centerPoint.x - point.x) <= distance && abs(centerPoint.y - point.y) <= distance) {
    onClick();
    return true;
  }
  return false;
};

void clearAllEventReceptors(){
  EventReceptor* temp = lastEventReceptor;
  while(lastEventReceptor != nullptr) {
    temp = lastEventReceptor;
    lastEventReceptor = lastEventReceptor->prev;
    delete temp;    
  }
}
#include "Screens.h";
#include <Arduino.h>;
#include "BaseScreen.h";

ScreenInitialMenu* Screens::initial = nullptr;
ScreenLearning* Screens::learning = nullptr;
BaseScreen* Screens::currentScreen = nullptr;

static BaseScreen* Screens::get(char* varName) {    
  Serial.println("getting screen " + String(varName));
  if (varName == "initial") {
    Serial.println("is initial");
    if (Screens::initial == nullptr) {
      Serial.println("is null");
      Screens::initial = new ScreenInitialMenu();
      Serial.println("returning initial");
      return initial;
    } else {
      Serial.println("is not null");
    };
  } else if (varName == "learning") {
    if (learning == nullptr) {
      Screens::learning = new ScreenLearning();
      return learning;
    };
  };
  return nullptr;
};
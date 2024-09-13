#include "Screens.h"
#include <Arduino.h>
#include <StackArray.h>
#include "BaseScreen.h"
#include "ScreenInitialMenu.h"
#include "ScreenLearning.h"
#include "ScreenPort.h"
#include "EVRcpt.h"


//STATIC INITIALIZATIONS
BaseScreen* Screens::currentScreen = nullptr;
StackArray <byte> Screens::stack;


//navigate to screen by id
void Screens::goTo(byte screenId,char* params[]) {      
  Serial.print("going screen ");
  Serial.println(screenId);

  BaseScreen* newScreen = nullptr;

  //find screen by id
  if (screenId == ScreenInitialMenu::SCREEN_ID) {
    newScreen = new ScreenInitialMenu();
  } else if (screenId == ScreenLearning::SCREEN_ID) {
    newScreen = new ScreenLearning();
  } else if (screenId == ScreenPort::SCREEN_ID) {
    newScreen = new ScreenPort();
  };

  if (newScreen != nullptr) {    

    //clear memory
    clearAllEVRcpts();
    if (currentScreen != nullptr) {
      delete currentScreen;
      currentScreen = nullptr;
    }
    currentScreen = newScreen;

    //add to stack if is not on top
    if (!stack.isEmpty()) {
      if (stack.peek() != screenId) {
        stack.push(screenId);
      }
    } else {
      stack.push(screenId);
    }

    //screen draw
    currentScreen->draw(params);
  } else {
    Serial.println("screen not found: " + String(screenId));
  }
};

//navigate to previous screen on stack
void Screens::goBack(char* params[]) {
  stack.pop();
  Screens::goTo(stack.peek(),params);
}
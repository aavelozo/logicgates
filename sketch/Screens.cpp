#include "Screens.h";
#include <Arduino.h>;
#include <StackArray.h>
#include "BaseScreen.h";
#include "ScreenInitialMenu.h";
#include "ScreenLearning.h";
#include "ScreenPort.h";


//STATIC INITIALIZATIONS
BaseScreen* Screens::currentScreen = nullptr;
StackArray <byte> Screens::stack;


//navigate to screen by id
static void Screens::goTo(byte screenId) {    
  Serial.print("going screen ");
  Serial.println(screenId);

  //clear memory
  if (currentScreen != nullptr) {
    delete currentScreen;
    currentScreen = nullptr;
  }    

  //find screen by id
  if (screenId == ScreenInitialMenu::SCREEN_ID) {
    currentScreen = new ScreenInitialMenu();
  } else if (screenId == ScreenLearning::SCREEN_ID) {
    currentScreen = new ScreenLearning();
  } else if (screenId == ScreenPort::SCREEN_ID) {
    currentScreen = new ScreenPort();
  };

  if (currentScreen != nullptr) {

    //add to stack if is not on top
    if (!stack.isEmpty()) {
      if (stack.peek() != screenId) {
        stack.push(screenId);
      }
    } else {
      stack.push(screenId);
    }

    //screen draw
    currentScreen->draw();
  } else {
    Serial.println("screen not found: " + String(screenId));
  }
};

//navigate to previous screen on stack
static void Screens::goBack() {
  stack.pop();
  Screens::goTo(stack.peek());
}
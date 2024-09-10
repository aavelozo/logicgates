#ifndef SCREENS_H
#define SCREENS_H

#include "BaseScreen.h";
#include <StackArray.h>

struct Screens {
  static StackArray <byte> stack;
  static BaseScreen* currentScreen;  
  static void goTo(byte screenId);    
  static void goBack();
};

#endif //SCREENS_H
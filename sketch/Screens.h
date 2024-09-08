#ifndef SCREENS_H
#define SCREENS_H

#import "ScreenInitialMenu.h";
#import "ScreenLearning.h";

struct Screens {
  static ScreenInitialMenu* initial;
  static ScreenLearning* learning;
  static BaseScreen* currentScreen;
  static BaseScreen* get(char* varName);
};



#endif SCREENS_H
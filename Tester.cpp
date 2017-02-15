//Tests.cpp
#include "Base.h"

Tester::Tester(){
  
}

Tester::~Tester(){
  
}

int Tester::begin(){
  if(Base.createWindow("Game Tester", 0, 0, 1280, 720, WindowFlag::DEFAULT_FLAGS) != 0){
    return -1;
  }
  while(){
    ///Game Logic
    //Rendering
  }
  return 0;
}

int Tester::end(){
  WindowManager.dispose();
}
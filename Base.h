///Base.h
#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "WindowManager.h"

#include <vector>
#include <string>
#include <iostream>

namespace EngineErrorType{
  enum e_type{
    SDL_INIT = 1,
    DISPLAY_INFO,
    WINDOW_CREATE,
    GL_INIT
  }
}

struct EngineError{
  EngineError(EngineErrorType::e_type errorType, char* error){ 
    error = "Error " + std::to_string(errorType) + "\n\t" << error; 
  }
  std::string error;
}

class Base{
public:  
  static int initBackend();
  static int createWindow(char* title, int x, int y int width, int height);
  
  static void reportError(EngineError error);
  static const char* errorReport();
  
private:
  WindowManager m_windowManager;
  std::vector<EngineError> m_EngineErrorBuffer;
  std::string m_customErrorBuffer = "";
};
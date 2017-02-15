///Base.cpp
#include <cstdio>

int Base::initBackend(){
  //Initialize SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    reportError(EngineError(EngineErrorType::SDL_INIT, "SDL error during initialization: " + SDL_GetError()));
    return -1;
  }
  if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
    reportError(EngineError(EngineErrorType::SDL_INIT, "SDL error during doublebuffer set: " + SDL_GetError()));
  }
  
  if(SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1)){
    reportError(EngineError(EngineErrorType::SDL_INIT, "SDL error during accelerated set: " + SDL_GetError()));
  }
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, 1)){
    reportError(EngineError(EngineErrorType::SDL_INIT, "SDL error during compatibility set: " + SDL_GetError()));
  }
}

int Base::createWindow(char* title, int x, int y int width, int height, WindowFlag flags){
  m_windowManager.createWindow(title, x, y, width, height, flags);
}

/** Error Reporting **/
void Base::reportError(EngineError error){
  m_EngineErrorBuffer.push_back(error);
}

// Print out the current error list and return it
const char* Base::errorReport(){
  std::string errorBuffer = "Errors: \n" + m_customErrorBuffer + '\n';
  for(auto& error : m_EngineErrorBuffer){
    errorBuffer += error.error;
  }
  std::printf("%s", errorBuffer.c_str());
  return errorBuffer.c_str();
}
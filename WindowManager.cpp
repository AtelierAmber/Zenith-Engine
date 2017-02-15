//WindowManager.cpp
#include <SDL/SDL.h>

WindowManager::WindowManager(){
  //Get display settings
  if(SDL_GetDesktopDisplayMode(0, &m_displayInfo) != 0){
    Base.recordError(EngineError(EngineErrorType::DISPLAY_INFO, "SDL error while getting display info: " + SDL_GetError()));
  }
}

WindowManager::~WindowManager(){
  
}

int WindowManager::createWindow(const char* title, int x, int y, int width, int height, Uint32 windowFlags){  
  ///Set Window flags
  Uint32 flags = 
    SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
  
  if (windowFlags & INVISIBLE) {
    flags |= SDL_WINDOW_HIDDEN;
  }
  if (windowFlags & FULLSCREEN) {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    m_screenHeight = display.h;
    m_screenWidth = display.w;
  }
  if (windowFlags & BORDERLESS) {
    flags |= SDL_WINDOW_BORDERLESS;
  }
  
  ///Create window
  m_window = SDL_CreateWindow(title, x, y, width, height, flags);
  if(m_window == nullptr){
    Base.recordError(EngineError(EngineErrorType::WINDOW_CREATE, "SDL error while creating the window: " + SDL_GetError()));
    return -1;
  }
  
  ///Setup the window
  //Set up our OpenGL context
  SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
  if(glContext == nullptr) Base.recordError(EngineError(EngineErrorType::GL_INIT, "SDL context creation error: " + SDL_GetError()))
    
  //Set up glew (optional but recommended)
  GLenum error = glewInit();
  if(error != GLEW_OK) Base.recordError(EngineError(EngineErrorType::GL_INIT, "Glew failed to initialize: " + glewGetErrorString(error)));

  //Check the OpenGL version
  std::printf("\n\n***   OpenGL Version: %s   ***\n\n", glGetString(GL_VERSION));

  //Set VSYNC
  SDL_GL_SetSwapInterval(0);

  // Enable alpha blend
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  return 0;
}

int WindowManager::updateWindow(){
  SDL_GL_SwapWindow(m_window);
}

void WindowManager::dispose(){
  
}
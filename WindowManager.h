//WindowManager.h
class SDL_Window;

namespace WindowFlag{
  enum w_flags{
    DEFAULT_FLAGS = 1,
    INVISIBLE = 1 >> 1, 
    FULLSCREEN = 1 >> 2, 
    BORDERLESS = 1 >> 3
  };
}

class WindowManger{
public:
  WindowManager();
  ~WindowManager();
  
  int createWindow(const char* title, int x, int y, int width, int height, Uint32 windowFlags);
  int updateWindow();
  void dispose();
  
  SDL_Window* getWindow() const { return m_window; }
  const int& getWindowWidth() const { return m_windowWidth; }
  const int& getWindowHeight() const { return m_windowHeight; }
  
  void resizeWindow(int w, int h);
  void centerWindow();
  
private:

  SDL_DisplayMode m_displayInfo;
  SDL_Window* m_window = nullptr;
  int m_windowWidth;
  int m_windowHeight;
};
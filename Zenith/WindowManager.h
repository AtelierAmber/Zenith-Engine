#pragma once
#include <SDL/SDL.h>
#include "Logger.h"

namespace Zenith {
    enum WindowFlag {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4,
        CENTERED = 0x8
    };

    enum class WindowMessage {
        QUIT = 0x1,
        CENTER = 0x2
    };

    class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        int createWindow(const char* title, int x, int y, unsigned int width, 
                         unsigned int height, unsigned int windowFlags);
        int update(); /**< Returns !0 on quit*/
        void dispose();

        void recieveMessage(const WindowMessage& message);

        SDL_Window* getContext() const { return m_window; }
        const SDL_DisplayMode& getDisplay() const { return m_displayInfo; }
        unsigned int getHeight() const { return m_winHeight; }
        unsigned int getWidth() const { return m_winWidth; }

    private:
        void centerWindow();

        SDL_DisplayMode m_displayInfo;
        SDL_Window* m_window;
        unsigned int m_winHeight, m_winWidth;

        int messageQueue = 0;

        Logger m_windowLog;
    };
}
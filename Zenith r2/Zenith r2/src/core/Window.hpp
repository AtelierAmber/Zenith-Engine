#pragma once
#include <SDL/SDL.h>

typedef unsigned int WindowFlags;

namespace zen {
    enum WindowFlag {
        INVISIBLE = 0b1,
        FULLSCREEN = 0b10,
        BORDERLESS = 0b100,
        RESIZABLE = 0b1000,
        CENTERED = 0b10000,
        VSYNC = 0b100000,
        CURSOR_HIDDEN = 0b1000000,
        CURSOR_TRAP = 0b10000000
    };

    class Window {
    public:
        Window();
        Window(const char* title, int x, int y, unsigned short width,
               unsigned short height, WindowFlags flags);
        ~Window();

        void recreate(int x, int y, unsigned short width,
                         unsigned short height, WindowFlags flags);
        void retitle(const char* title);

        void center();
        void sync(bool enable);

        int update();
        void close();

        bool isSynced() const { return m_vsync; }
        const SDL_Window* getContext() const { return m_window; }
        const SDL_DisplayMode& getDisplay() const { return m_displayInfo; }
        unsigned short height() const { return m_winHeight; }
        unsigned short width() const { return m_winWidth; }

    private:
        SDL_DisplayMode m_displayInfo;
        SDL_Window* m_window = nullptr;
        unsigned short m_winHeight = 0, m_winWidth = 0;
        const char* m_title;
        bool m_vsync = true;
    };
}
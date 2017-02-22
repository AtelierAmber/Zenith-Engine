///Base.h
#pragma once

#include "WindowManager.h"

#include <iostream>

namespace Zenith {
    class Core {
    public:
        Core() {}
        ~Core() { dispose(); }
        WindowManager* getWindowManager() { return &m_windowManager; }
        int start(const char* title, int x, int y, int width, int height, Uint32 flags);

        void dispose();
    private:
        int createWindow(const char* title, int x, int y, int width, int height, Uint32 flags);
        int initBackend();
        WindowManager m_windowManager;
    };
}
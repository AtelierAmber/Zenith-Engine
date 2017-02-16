///Base.h
#pragma once

#include "WindowManager.h"

#include <iostream>

namespace Zenith {
    enum class GameState {
        IDLE,
        EXIT
    };

    class Core {
    public:
        Core() {}
        ~Core() { dispose(); }
        WindowManager* getWindowManager() { return &m_windowManager; }
        int start(const char* title, int x, int y, int width, int height, Uint32 flags);
        void editGameState(GameState state) { m_gameState = state; }
        void processInput();

        void dispose();
    private:
        int createWindow(const char* title, int x, int y, int width, int height, Uint32 flags);
        int initBackend();
        WindowManager m_windowManager;
        GameState m_gameState;
    };
}
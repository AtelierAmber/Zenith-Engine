///Base.cpp
#include "Core/Core.h"
#include "Logging/Logger.h"
#include <cstdio>

namespace Zenith {
    int Core::start(const char* title, int x, int y, int width, int height, Uint32 flags) {
        if (initBackend() != 0) {
            return -1;
        }
        if (createWindow(title, x, y, width, height, flags) != 0) {
            return -2;
        }
        while (m_gameState != GameState::EXIT) {
            processInput();
        }
        return 0;
    }

    int Core::initBackend() {
        //Clear past logs
        Log::refresh();
        //Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            Log::logError("SDL error during initialization: " + std::string(SDL_GetError()));
            return -1;
        }
        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
            Log::logWarning("SDL error during doublebuffer set: " + std::string(SDL_GetError()));
        }

        if (SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1)) {
            Log::logWarning("SDL error during accelerated set: " + std::string(SDL_GetError()));
        }
        Log::logEvent("Backend finished initialization");
        return 0;
    }

    int Core::createWindow(const char* title, int x, int y, int width, int height, Uint32 flags) {
        return m_windowManager.createWindow(title, x, y, width, height, flags);
    }

    void Core::processInput() {
        SDL_Event evnt;
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
            case SDL_QUIT:
                m_gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                evnt.motion.x;
                evnt.motion.y;
                break;
            default:
                
                break;
            }
        }
    }

    void Core::dispose() {
        m_windowManager.dispose();
    }
}

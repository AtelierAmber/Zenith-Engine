//WindowManager.cpp
#include <GL/glew.h>

#include "Core/WindowManager.h"
#include "Logging/Logger.h"

namespace Zenith {
    WindowManager::WindowManager() {
        
    }

    WindowManager::~WindowManager() {

    }

    int WindowManager::createWindow(const char* title, int x, int y, int width, int height, Uint32 windowFlags) {
        //Get display settings
        if (SDL_GetDesktopDisplayMode(0, &m_displayInfo) != 0) {
            Log::logWarning("SDL error while getting display info: " + std::string(SDL_GetError()));
        }
        else Log::logEvent("Desktop info successfully acquired");

        ///Set Window flags
        Uint32 flags =
            SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
        if (windowFlags & WindowFlag::INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
            Log::logEvent("Window set to invisible");
        }
        if (windowFlags & WindowFlag::FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            Log::logEvent("Window set to fullscreen");
            m_windowHeight = m_displayInfo.h;
            m_windowWidth = m_displayInfo.w;
        }
        else {
            m_windowHeight = height;
            m_windowWidth = width;
        }
        if (windowFlags & WindowFlag::BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
            Log::logEvent("Window set to borderless");
        }

        ///Create window
        m_window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (m_window == nullptr) {
            Log::logError("SDL error while creating the window: " + std::string(SDL_GetError()));
            return -1;
        }
        if (windowFlags & WindowFlag::CENTERED) {
            centerWindow();
        }

        ///Setup the window
        //Set up our OpenGL context
        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
        if (glContext == NULL) Log::logWarning("SDL context creation error: " + std::string(SDL_GetError()));

        //Set up glew
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            Log::logWarning("Glew failed to initialize: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(error))));
        }

        //Set the viewport
        glViewport(0, 0, width, height);
        
        //Check the OpenGL version
        std::printf("\n\n***   OpenGL Version: %s   ***\n\n", glGetString(GL_VERSION));

        //Set VSYNC
        SDL_GL_SetSwapInterval(0);

        //Default background color to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Enable alpha blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Log::logEvent("Window successfully created with OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

        return 0;
    }

    int WindowManager::updateWindow() {
        SDL_GL_SwapWindow(m_window);
        return 0;
    }

    void WindowManager::dispose() {
        
    }

    void WindowManager::resizeWindow(int w, int h) {
        m_windowHeight = h;
        m_windowWidth = w;
    }

    void WindowManager::centerWindow() {
        SDL_SetWindowPosition(m_window, (m_displayInfo.w / 2) - (m_windowWidth / 2),
            (m_displayInfo.h / 2) - (m_windowHeight / 2));
    }

}
#include "WindowManager.h"

#include <GL/glew.h>

namespace Zenith {
    WindowManager::WindowManager() {
        m_windowLog.construct("system.log", "WNDW");
    }

    WindowManager::~WindowManager() {}

    void WindowManager::dispose() {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void WindowManager::recieveMessage(const WindowMessage& message) {
        messageQueue |= (int)message;
    }

    int WindowManager::createWindow(const char* title, int x, int y, unsigned int width, unsigned int height, unsigned int windowFlags) {
        //Get display settings
        if (SDL_GetDesktopDisplayMode(0, &m_displayInfo) != 0) {
            m_windowLog.log("WNDW", LogType::WARNING, "SDL error while getting display info: " + std::string(SDL_GetError()));
        }
        else m_windowLog.log("WNDW", LogType::EVENT, "Desktop info successfully acquired");

        ///Set Window flags
        Uint32 flags =
            SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
        if (windowFlags & WindowFlag::INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
            m_windowLog.log("WNDW", LogType::EVENT, "Window set to invisible");
        }
        if (windowFlags & WindowFlag::FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            m_windowLog.log("WNDW", LogType::EVENT, "Window set to fullscreen");
            m_winHeight = m_displayInfo.h;
            m_winWidth = m_displayInfo.w;
        }
        else {
            m_winHeight = height;
            m_winWidth = width;
        }
        if (windowFlags & WindowFlag::BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
            m_windowLog.log("WNDW", LogType::EVENT, "Window set to borderless");
        }
        if (windowFlags & WindowFlag::CURSOR_HIDDEN) {
            SDL_ShowCursor(SDL_DISABLE);
        }

        ///Create window
        m_window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (m_window == nullptr) {
            m_windowLog.log("WNDW", LogType::ERROR, "SDL error while creating the window: " + std::string(SDL_GetError()));
            return -1;
        }
        if (windowFlags & WindowFlag::CENTERED) {
            centerWindow();
        }
        if (windowFlags & WindowFlag::CURSOR_TRAP) {
            SDL_SetWindowGrab(m_window, SDL_TRUE);
            if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1) {
                m_windowLog.log("WNDW", LogType::WARNING, "SDL Relative mouse mode not supported!");
            }
        }

        ///Setup the window
        //Set up our OpenGL context
        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
        if (glContext == NULL) {
            m_windowLog.log("WNDW", LogType::WARNING, "SDL context creation error: " + std::string(SDL_GetError()));
        }

        //Set up glew
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            m_windowLog.log("WNDW", LogType::WARNING, "Glew failed to initialize: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(error))));
        }

        //Set the viewport
        glViewport(0, 0, m_winWidth, m_winHeight);

        //Check the OpenGL version
        std::printf("\n\n***   OpenGL Version: %s   ***\n\n", glGetString(GL_VERSION));

        //Set VSYNC
        SDL_GL_SetSwapInterval(0);

        // Enable alpha blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_windowLog.log("WNDW", LogType::EVENT, "Window successfully created\n***   OpenGL Version: " + 
                        std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))) + "   ***");

        return 0;
    }

    int WindowManager::update() {
        SDL_GL_SwapWindow(m_window);
        if (messageQueue) {
            if (messageQueue & (int)WindowMessage::CENTER) {
                centerWindow();
            }
            if (messageQueue & (int)WindowMessage::QUIT) {
                return -1;
            }
        }
        return 0;
    }

    void WindowManager::centerWindow() {
        SDL_SetWindowPosition(m_window, (m_displayInfo.w / 2) - (m_winWidth / 2), 
                             (m_displayInfo.h / 2) - (m_winHeight / 2));
    }

}
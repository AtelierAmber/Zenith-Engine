#include "Window.hpp"

#include <GL/glew.h>

#include "debug/Logger.hpp"

namespace zen {
    Window::Window() { }

    Window::Window(const char* title, int x, int y, unsigned short width, 
                   unsigned short height, WindowFlags flags) {
        //Get display settings
        if(SDL_GetDesktopDisplayMode(0, &m_displayInfo) != 0) {
            Log::Debug({LogMajorType::WARNING}, "SDL error while getting display information! Err: ", SDL_GetError());
        } else Log::Debug({LogMajorType::EVENT}, "Display information successfully aquired");

        ///Set Window flags
        Uint32 wflags =
            SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
        if(flags & WindowFlag::INVISIBLE) {
            wflags |= SDL_WINDOW_HIDDEN;
            Log::Debug({LogMajorType::WARNING}, "Window was set to invisible?");
        }
        if(flags & WindowFlag::FULLSCREEN) {
            wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            m_winHeight = m_displayInfo.h;
            m_winWidth = m_displayInfo.w;
        } else {
            m_winHeight = height;
            m_winWidth = width;
        }
        if(flags & WindowFlag::BORDERLESS) {
            wflags |= SDL_WINDOW_BORDERLESS;
        }
        if(flags & WindowFlag::CURSOR_HIDDEN) {
            SDL_ShowCursor(SDL_DISABLE);
        }

        ///Create window
        m_window = SDL_CreateWindow(title, x, y, width, height, wflags);
        if(m_window == nullptr) {
            Log::Debug({LogMajorType::ERROR}, "Error: ", SDL_GetError(), " while creating the window!!");
        } else {
            if(flags & WindowFlag::CENTERED) {
                center();
            }
            if(flags & WindowFlag::CURSOR_TRAP) {
                SDL_SetWindowGrab(m_window, SDL_TRUE);
                if(SDL_SetRelativeMouseMode(SDL_TRUE) == -1) {
                    Log::Debug({LogMajorType::ERROR}, "SDL Relative Mouse Mode not supported!!");
                }
            }

            ///Setup the window
            //Set up our OpenGL context
            SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
            if(glContext == NULL) {
                Log::Debug({LogMajorType::ERROR}, "Error: ", SDL_GetError(), " while creating OpenGL window context!!");
            }

            //Set up glew
            GLenum error = glewInit();
            if(error != GLEW_OK) {
                Log::Debug({LogMajorType::ERROR}, "Glew failed to initialize! Err: ", glewGetErrorString(error));
            }

            //Set the viewport
            glViewport(0, 0, m_winWidth, m_winHeight);

            //Set VSYNC
            if(flags & WindowFlag::VSYNC) {
                m_vsync = true;
                SDL_GL_SetSwapInterval(1);
            } else {
                m_vsync = false;
                SDL_GL_SetSwapInterval(0);
            }

            // Enable alpha blend
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            Log::Debug({LogMajorType::EVENT}, "Window successfully created with OpenGL version: ", glGetString(GL_VERSION));
            std::printf("\n\n***   OpenGL Version: %s   ***\n\n", glGetString(GL_VERSION));
        }
    }

    Window::~Window() { }

    void Window::recreate(int x, int y, unsigned short width, unsigned short height,
                          WindowFlags flags) {
        close();
        ///Set Window flags
        Uint32 wflags =
            SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
        if(flags & WindowFlag::INVISIBLE) {
            wflags |= SDL_WINDOW_HIDDEN;
            Log::Debug({LogMajorType::WARNING}, "Window was set to invisible?");
        }
        if(flags & WindowFlag::FULLSCREEN) {
            wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            m_winHeight = m_displayInfo.h;
            m_winWidth = m_displayInfo.w;
        } else {
            m_winHeight = height;
            m_winWidth = width;
        }
        if(flags & WindowFlag::BORDERLESS) {
            wflags |= SDL_WINDOW_BORDERLESS;
        }
        if(flags & WindowFlag::CURSOR_HIDDEN) {
            SDL_ShowCursor(SDL_DISABLE);
        }
        if(flags & WindowFlag::RESIZABLE) {
            wflags |= SDL_WINDOW_RESIZABLE;
        }

        ///Create window
        m_window = SDL_CreateWindow(m_title, x, y, width, height, wflags);
        if(m_window == nullptr) {
            Log::Debug({LogMajorType::ERROR}, "Error: ", SDL_GetError(), " while creating the window!!");
        } else {
            if(flags & WindowFlag::CENTERED) {
                center();
            }
            if(flags & WindowFlag::CURSOR_TRAP) {
                SDL_SetWindowGrab(m_window, SDL_TRUE);
                if(SDL_SetRelativeMouseMode(SDL_TRUE) == -1) {
                    Log::Debug({LogMajorType::ERROR}, "SDL Relative Mouse Mode not supported!!");
                }
            }

            ///Setup the window
            //Set up our OpenGL context
            SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
            if(glContext == NULL) {
                Log::Debug({LogMajorType::ERROR}, "Error: ", SDL_GetError(), " while creating OpenGL window context!!");
            }

            //Set up glew
            GLenum error = glewInit();
            if(error != GLEW_OK) {
                Log::Debug({LogMajorType::ERROR}, "Glew failed to initialize! Err: ", glewGetErrorString(error));
            }

            //Set the viewport
            glViewport(0, 0, m_winWidth, m_winHeight);

            //Set VSYNC
            if(flags & WindowFlag::VSYNC) {
                m_vsync = true;
                SDL_GL_SetSwapInterval(1);
            } else {
                m_vsync = false;
                SDL_GL_SetSwapInterval(0);
            }

            // Enable alpha blend
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            Log::Debug({LogMajorType::EVENT}, "Window successfully recreated with OpenGL version: ", glGetString(GL_VERSION));
            std::printf("\n\n***   OpenGL Version: %s   ***\n\n", glGetString(GL_VERSION));
        }
    }

    void Window::retitle(const char* title) {
        if(m_window != nullptr) {
            m_title = title;
            SDL_SetWindowTitle(m_window, title);
        }
    }

    void Window::center() {
        SDL_SetWindowPosition(m_window, (m_displayInfo.w / 2) - (m_winWidth / 2),
            (m_displayInfo.h / 2) - (m_winHeight / 2));
    }

    void Window::sync(bool enable) {
        if(enable) {
            m_vsync = true;
            SDL_GL_SetSwapInterval(1);
        } else {
            m_vsync = false;
            SDL_GL_SetSwapInterval(0);
        }
    }

    int Window::update() {
        SDL_GL_SwapWindow(m_window);
        return 0;
    }

    void Window::close() {
        if(m_window != nullptr) {
            SDL_DestroyWindow(m_window);
        }
    }

}
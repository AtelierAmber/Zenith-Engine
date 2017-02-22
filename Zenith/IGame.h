#pragma once

#include "SceneManager.h"
#include "WindowManager.h"
#include "InputManager.h"

namespace Zenith {
    class IGame {
    public:
        IGame();
        ~IGame();

        /* Initialize and start the game */
        int start(const char* title = "Zenith Game", int x = 0, int y = 0, unsigned int width = 1280, unsigned int height = 720, unsigned int windowFlags = 0);

    protected:
        /* Called on game start
         * Used for scene independent variables */
        virtual void build() = 0;

        /* Called every game step 
         * Used for scene independent variables */
        virtual void IUpdate() = 0;

        /* Called on game exit
         * Used for scene independent variables */
        virtual void destroy() = 0;

        bool m_running = true;
        WindowManager m_windowManager;
        InputManager m_inputManager;
        SceneManager m_sceneManager;
    private:
        /* Runs the game */
        int run();

        /* Update systems, scenes, etc. */
        void update();
    };
}
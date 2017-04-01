#pragma once
#include "core/Window.hpp"
#include "IScene.hpp"
#include "core/Timing.hpp"

namespace zen {
    class IGame {
    public:
        IGame();
        virtual ~IGame() = 0;

        int start(const char* title, int x, int y, int width, int height, WindowFlags flags);
        void stop();

        Window* getWindow() { return &m_window; }

        float getRunningFPS() { return m_fps; }

    protected:
        /* Call to add a scene to the game 
         * This does NOT `delete` a scene when it is done! */
        void addScene(IScene* scene);

        /* Called on game start
         * Used for scene independent variables */
        virtual void build() = 0;

        /* Called every game step 
         * Used for scene independent variables */
        virtual void update() = 0;

        /* Called on game exit
         * Used for game independent variables */
        virtual void destroy() = 0;

        Window m_window;
    private:
        /* Update core systems and scenes */
        void run();

        FpsLimiter m_limiter;

        float m_fps;
        bool m_running = true;
    };
}
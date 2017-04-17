#pragma once

#include <SDL/SDL.h>

#define MS_PER_SEC 1000.0f

namespace zen {
    ///Calculates FPS and limits FPS
    class FpsLimiter {
    public:
        FpsLimiter();

        // Initializes the FPS limiter. For now, this is
        // analogous to setMaxFPS
        void init(float maxFPS);

        // Sets the desired max FPS
        void setMaxFPS(float maxFPS);
        float getMaxFPS() { return m_maxFPS; }

        void begin();

        // end() will return the current FPS as a float
        float end();
    private:
        // Calculates the current FPS
        void calculateFPS();

        // Variables
        float m_maxFPS = 60.0f;
        float m_fps;
        Uint32 m_frameTime;
        Uint32 m_startTicks;
    };

}
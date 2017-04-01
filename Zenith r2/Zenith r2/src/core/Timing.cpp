#include "Timing.hpp"

namespace zen {

    FpsLimiter::FpsLimiter() {}
    void FpsLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }

    void FpsLimiter::setMaxFPS(float maxFPS) {
        m_maxFPS = maxFPS;
    }

    void FpsLimiter::begin() {
        m_startTicks = SDL_GetTicks();
    }

    float FpsLimiter::end() {
        calculateFPS();

        Uint32 frameTicks = SDL_GetTicks() - m_startTicks;
        //Limit the FPS to the max FPS
        if(MS_PER_SEC / m_maxFPS > frameTicks) {
            SDL_Delay((Uint32)(MS_PER_SEC / m_maxFPS - frameTicks));
        }

        return m_fps;
    }

    void FpsLimiter::calculateFPS() {
        //The number of frames to average
        static const int NUM_SAMPLES = 10;
        //Stores all the frametimes for each frame that we will average
        static Uint32 frameTimes[NUM_SAMPLES];
        //The current frame we are on
        static unsigned int currentFrame = 0;
        //the ticks of the previous frame
        static Uint32 prevTicks = SDL_GetTicks();

        //Ticks for the current frame
        Uint32 currentTicks = SDL_GetTicks();

        //Calculate the number of ticks (ms) for this frame
        m_frameTime = currentTicks - prevTicks;
        frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

        //current ticks is now previous ticks
        prevTicks = currentTicks;

        //The number of frames to average
        int count;

        currentFrame++;
        if(currentFrame < NUM_SAMPLES) {
            count = currentFrame;
        } else {
            count = NUM_SAMPLES;
        }

        //Average all the frame times
        float frameTimeAverage = 0.0f;
        for(int i = 0; i < count; i++) {
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= (float)count;

        //Calculate FPS
        if(frameTimeAverage > 0.0f) {
            m_fps = MS_PER_SEC / frameTimeAverage;
        } else {
            m_fps = 60.0f;
        }
    }

}
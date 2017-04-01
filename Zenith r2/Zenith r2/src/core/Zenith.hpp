#pragma once
#include <SDL/SDL.h>

#include "debug/Logger.hpp"

namespace zen {
    static int init() {
        if(SDL_Init(SDL_INIT_EVERYTHING)) {
            Log::Debug({LogMajorType::ERROR}, "Could not initialize SDL! Err: ", SDL_GetError());
            return -1;
        }
        if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
            Log::Debug({LogMajorType::ERROR}, "Could not enable SDL Double buffering! Err: ", SDL_GetError());
        }

        if(SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1)) {
            Log::Debug({LogMajorType::ERROR}, "Error during GL_Accelerated_Visuals enable! Err: ", SDL_GetError());
        }
        Log::Debug({LogMajorType::EVENT}, "SDL Initialization completed");
        return 0;
    }
}
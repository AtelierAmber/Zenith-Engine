#include "Zenith.h"

#include <SDL/SDL.h>
#include "Logger.h"

namespace Zenith {
    namespace Core {
        int init() {
            Logger logger("system.log");
            if (SDL_Init(SDL_INIT_EVERYTHING)) {
                logger.log(LogType::ERROR, "Could not initialize SDL: " + std::string(SDL_GetError()));
                return -1;
            }
            if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
                logger.log(LogType::WARNING, "SDL error during doublebuffer set: " + std::string(SDL_GetError()));
            }

            if (SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1)) {
                logger.log(LogType::WARNING, "SDL error during accelerated set: " + std::string(SDL_GetError()));
            }
            logger.log(LogType::EVENT, "Backend finished initialization");
            return 0;
        }
    }
}
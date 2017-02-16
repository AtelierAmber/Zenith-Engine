#include "Interfaces/IGameCore.h"
#include <GL/glew.h>

namespace Zenith {
    IGameCore::IGameCore(const char* title, int x, int y, int width, int height, unsigned int flags) {
        m_core = new Zenith::Core();
        m_core->start(title, x, y, width, height, flags);
        m_shader.compile();
    }

    IGameCore::~IGameCore() { /* Empty */ }

    int IGameCore::run() {
        float verticies[9] = {
            -0.5f, 0.5f, 0.0f, //Top left
            -0.5f, -0.5f, 0.0f, //Bottom left
            0.5f, -0.5f, 0.0f //Top right
        };
        int indicies[3] = { 0, 1, 2 };

        m_testModel = m_modelLoader.loadToVAO(verticies, 9, indicies, 3);
        while (m_gameState != GameState::EXIT) {
            processInput();
            IDraw();
        }
        m_shader.dispose();
        m_core->dispose();
        return 0;
    }

    void IGameCore::IDraw() {
        m_renderer.prepare();
        m_shader.start();
        m_renderer.render(m_testModel);
        m_shader.end();
        m_core->getWindowManager()->updateWindow();
    }

    void IGameCore::processInput() {
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

}
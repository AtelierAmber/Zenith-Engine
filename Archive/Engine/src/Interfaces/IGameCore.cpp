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
            0.0f, 0.5f, 0.0f, //Top
            -0.5f, -0.5f, 0.0f, //Bottom left
            0.5f, -0.5f, 0.0f //Bottom right
        };
        float textureCoords[6] = {
            0.5f, 1.0f, //Top 
            0.0f, 0.0f, //Bottom Left
            1.0f, 0.0f //Bottom Right
        };
        int indicies[3] = { 0, 1, 2 };

        m_testModel = m_modelLoader.loadToVAO(verticies, 9, textureCoords, indicies, 3);
        m_testTexture = m_modelLoader.loadTexture("Tester/res/textures/wall.png");
        m_testModelTextured = TexturedModel(m_testModel, m_testTexture);
        m_testEntity = Entity(m_testModelTextured, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
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
        m_renderer.render(m_testEntity, m_shader);
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
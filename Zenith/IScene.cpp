#include "IScene.h"

namespace Zenith {
    IScene::IScene() {
        m_logger.construct("scene.log", "SCEN");
    }

    IScene::IScene(IGame* game) {
        setGame(game);
        m_logger.construct("scene.log", "SCEN");
    }

    IScene::~IScene() {
        m_renderer.dispose();
        m_game = nullptr;
    }

    void IScene::coreRender() {
        m_renderer.begin();
        render();
        m_renderer.end();
    }
}
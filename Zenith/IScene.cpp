#include "IScene.h"

#include "IGame.h"

namespace Zenith {
    IScene::IScene() {
        m_logger.construct("scene.log", "SCEN");
    }

    IScene::IScene(IGame* const game) {
        setGame(game);
        m_logger.construct("scene.log", "SCEN");
    }

    IScene::~IScene() {

    }

    void IScene::coreRender() {
        m_renderer.begin();
        render();
        m_renderer.end();
    }

    bool IScene::keyStateIs(KeyID key /* Key::__ or Key::Modifier::__ */, KeyState state) {
        return (m_game->getInputManager()->keyState(key) == state);
    }

    void IScene::dispose() {
        m_renderer.dispose();
        m_game = nullptr;
    }
}
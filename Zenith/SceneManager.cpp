#include "SceneManager.h"
#include "IGame.h"
#include "IScene.h"

namespace Zenith {
    SceneManager::SceneManager(IGame* game) : m_game(game) {}

    SceneManager::~SceneManager() { destroy(); }

    int SceneManager::next() {
        if (m_currentScene == m_scenes.size()-1) {
            return -1;
        }
        return ++m_currentScene;
    }

    int SceneManager::previous() {
        if (m_currentScene <= 0) {
            return -1;
        }
        m_scenes[m_currentScene]->exit();
        --m_currentScene;
        m_scenes[m_currentScene]->enter();
        return m_currentScene;
    }

    int SceneManager::gotoScene(unsigned int index) {
        if (index > m_scenes.size()) {
            return -1;
        }
        m_currentScene = index;
        return 0;
    }

    unsigned int SceneManager::addScene(IScene* scene) {
        scene->m_sceneIndex = (unsigned int)m_scenes.size();
        if ((int)m_scenes.size() == 0) m_currentScene = 0;
        m_scenes.push_back(scene);
        scene->setGame(m_game);
        scene->build();
        return scene->m_sceneIndex;
    }

    Zenith::IScene* SceneManager::getCurrent() {
        if (m_currentScene != -1) {
            return m_scenes[m_currentScene];
        }
        return nullptr;
    }

    void SceneManager::destroy() {
        if (m_scenes.size() > 0) {
            m_scenes[m_currentScene]->exit();
            for (auto& scene : m_scenes) {
                scene->destroy();
            }
            m_scenes.resize(0);
            m_currentScene = 0;
        }
    }

}
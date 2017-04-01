#include "SceneController.hpp"

namespace zen {

    SceneController::SceneController(){ }

    SceneController::~SceneController() {}

    void SceneController::gotoNext() {
        m_state = ControlState::GOTO_NEXT;
    }

    void SceneController::gotoPrev() {
        m_state = ControlState::GOTO_PREV;
    }

    void SceneController::add(IScene& scene, IGame* parentGame) {

    }

    void SceneController::remove(IScene& scene) {

    }

    void SceneController::updateCurrent() {
        /* Check for state change */
        switch(m_state) {
        case ControlState::GOTO_NEXT:
            if(next() != -1) {

            }
            m_state = ControlState::IDLE;
            break;
        case ControlState::GOTO_PREV:
            if(previous() != -1) {

            }
            m_state = ControlState::IDLE;
            break;
        }
        currentScene()->coreUpdate();
    }

    void SceneController::renderCurrent() {
        currentScene()->coreRender();
    }

    zen::IScene* SceneController::currentScene() {
        return m_scenes[m_currentScene];
    }

    int SceneController::next() {
        int nextS = m_scenes[m_currentScene]->m_nextScreen;
        if(nextS >= m_scenes.size()) {
            return -1;
        }
        if(nextS < 0) {
            return (m_currentScene < m_scenes.size()-1) ? ++m_currentScene : -1;
        }
        m_currentScene = nextS;
        return m_currentScene;
    }

    int SceneController::previous() {
        int prevS = m_scenes[m_currentScene]->m_prevScreen;
        if(prevS >= m_scenes.size()) {
            return -1;
        }
        if(prevS < 0) {
            return (m_currentScene > 0) ? --m_currentScene : -1;
        }
        m_currentScene = prevS;
        return m_currentScene;
    }

    void SceneController::destroy() {
        for(auto& s : m_scenes) {
            s->destroy();
        }
        m_scenes.clear();
    }

}
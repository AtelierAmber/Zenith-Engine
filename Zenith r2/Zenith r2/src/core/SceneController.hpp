#pragma once
#include <vector>
#include "interface/IScene.hpp"

namespace zen {
    class IGame;
    enum class ControlState {
        IDLE,
        GOTO_NEXT,
        GOTO_PREV
    };

    class SceneController {
    public:
        SceneController();
        ~SceneController();

        void gotoNext();
        void gotoPrev();
        
        void add(IScene& scene, IGame* parentGame);
        void remove(IScene& scene);

        void updateCurrent();
        void renderCurrent();

        IScene* currentScene();
        void destroy();
    private:
        int next();
        int previous();

        std::vector<IScene*> m_scenes;
        ControlState m_state = ControlState::IDLE;
        unsigned int m_currentScene = 0;
    };
}
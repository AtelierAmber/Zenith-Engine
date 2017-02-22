#pragma once

#include <vector>

namespace Zenith {
    class IGame;
    class IScene;

    class SceneManager {
    public:
        SceneManager(IGame* game);
        ~SceneManager();

        int next(); /**< Returns -1 if reached end, otherwise returns index*/
        int previous();/**< Returns -1 if reached start, otherwise returns index*/

        int gotoScene(unsigned int index); /**< Returns -1 if index is out of bounds*/
        unsigned int addScene(IScene* scene);

        IScene* getCurrent();

        void destroy();
    private:
        IGame* m_game = nullptr;
        std::vector<IScene*> m_scenes;
        int m_currentScene = -1;
    };
}
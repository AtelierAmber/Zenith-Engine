#pragma once
#include "Renderer.h"
#include "DataLoader.h"
#include "Camera3D.h"

#include "KeyCode.h"

namespace Zenith {
    class IGame;

    enum class SceneState {
        IDLE,
        RUNNING,
        CONCLUDE,
        GAME_EXIT,
    };

    class IScene {
    public:
        friend class SceneManager;
        IScene();
        IScene(IGame* game);
        virtual ~IScene();

        /* Called when added to SceneManager */
        virtual void build() = 0;

        /* Called when set as current scene */
        virtual void enter() = 0;

        /* Called each draw update */
        void coreRender();
        virtual void render() = 0;

        /* Called each tick of the game */
        virtual void update() = 0;

        /* Called when exiting from */
        virtual void exit() = 0;

        /* Called when the scene is destroyed */
        virtual void destroy() = 0;

        void setGame(IGame* game) { m_game = game; }

        int getNext() { return m_nextScene; }
    protected:
        void setNext(unsigned int next) { m_nextScene = next; }

        bool keyStateIs(KeyID key /* Key::__ or Key::Modifier::__ */, KeyState state);

        Logger m_logger;
        DataLoader m_dataLoader;
        Camera3D m_camera;

        Renderer m_renderer;
        IGame* m_game = nullptr;
        int m_nextScene;
        unsigned int m_sceneIndex;

    private:
        void dispose();
    };
}
#pragma once

namespace zen {
    class IGame;

    enum class SceneState {
        IDLE,
        RUNNING,
        CONCLUDE_NEXT,
        CONCLUDE_PREV,
        GAME_EXIT,
    };

    class IScene {
        friend class SceneController;
    public:
        IScene(IGame* game, int next, int prev) : 
            m_nextScreen(next), m_prevScreen(prev) {}
        virtual ~IScene() = 0;

        SceneState state() { return m_state; }
    protected:
        /* Called when added to SceneManager */
        void init();
        virtual void build() = 0;

        /* Called when set as current scene */
        virtual void enter() = 0;

        /* Called each draw update */
        void coreRender();
        virtual void render() = 0;

        /* Called each tick of the game */
        void coreUpdate();
        virtual void update() = 0;

        /* Called when exiting from */
        virtual void exit() = 0;

        /* Called when the scene is destroyed */
        void dispose();
        virtual void destroy() = 0;

        /* Next and previous screen id's
         * -1 to proceed to the next one in the list */
        int m_nextScreen = -1;
        int m_prevScreen = -1;

        SceneState m_state;
        IGame* m_parentGame = nullptr;

        unsigned int m_id;
    private:
        
    };
}
#pragma once
#include <vector>

#include "core/Window.hpp"
#include "rendering/MasterRenderer.hpp"
#include "core/Timing.hpp"

typedef unsigned int SceneHandle;

namespace zen {
    typedef unsigned int SceneType;
    enum SceneFlag {
        RENDER_OVERRIDE = 0b1,
        UPDATE_OVERRIDE = 0b10,
        DEFAULT_FLAGS = 0b11
    };
    class IScene;

    class IEngine {
    public:
        IEngine();
        virtual ~IEngine() = 0 {}

        /* Starts the game */
        int start(const char* title = "NO TITLE", int x = 0, int y = 0, 
                  unsigned int width = 640, unsigned int height = 360, WindowFlags windowFlags = WindowFlag::WINDOW_DEFAULT);

        Window* getWindow() { return &m_window; }

        void pushScene(SceneHandle scene);
        void popScene(SceneHandle scene);
        void clearScenes();

        void quit() { m_running = false; }
        
        SceneHandle registerScene(IScene* scene, SceneType type = SceneFlag::DEFAULT_FLAGS, bool managedByEngine = false);
        template<class S, typename... Args>
        SceneHandle registerScene(SceneType type, Args... args) {
            return registerScene(new S(args...), type, true);
        }

        float FPS() { return m_FPS; }

    protected:
        /* Called on game start */
        virtual void build() = 0;

        /* Called every tick of the game */
        virtual void update(float deltaTime) = 0;

        /* Called on game exit */
        virtual void destroy() = 0;

    private:
        bool m_running = false;
        /* Runs the game */
        int run();
        void end();

        /* Update core devices */
        void Update(float deltaTime);
        void Tick();

        /* Capture SDL events */
        void registerEvents();

        /* Render game */
        void Render();

        Window m_window;
        MasterRenderer m_renderer;

        FpsLimiter m_fpsLimiter;
        float m_FPS = 0.0f;
        unsigned long m_gameTime = 0;

        struct SceneRef {
            IScene* scene = nullptr;
            SceneType type : 7;
            bool managed : 1;
        };
        std::vector<SceneRef> m_scenes;
        std::vector<SceneHandle> m_sceneQueue;
    };
}
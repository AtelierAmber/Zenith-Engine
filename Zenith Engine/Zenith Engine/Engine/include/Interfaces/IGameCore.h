#pragma once
#include "Core/Core.h"
#include "Rendering/ModelLoader.h"
#include "Rendering/Renderer.h"
#include "Rendering/StaticShader.h"

namespace Zenith {
    const float DESIRED_FPS = 60.0f;

    enum class GameState {
        IDLE,
        EXIT
    };

    class IGameCore
    {
    public:
        IGameCore(const char* title, int x, int y, int width, int height, unsigned int flags);
        ~IGameCore();

        //Runs the game
        int run();

        // Called on initialization
        virtual void onInit() = 0;
        // For adding all screens
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;

        void editGameState(GameState state) { m_gameState = state; }
    protected:
        WindowManager* windowManager() { return m_core->getWindowManager(); }

        ModelLoader m_modelLoader;
        Renderer m_renderer;
        StaticShader m_shader;
        GameState m_gameState;
        Zenith::Core* m_core;
    private:
        RawModel m_testModel;
        void IDraw();
        void processInput();
    };
}
#pragma once
#include "rendering/Rendering"

typedef unsigned int SceneHandle;

namespace zen {
    class IEngine;
    enum class SceneState {
        IDLE, //< Will render but won't run update()
        ACTIVE, //< Will render and call update()
        CONCLUDE, //< Will pop the scene next update
        GAME_QUIT //< Will flag the game to quit next frame
    };

    class IScene {
        friend class IEngine;
    public:
        virtual ~IScene() = 0 {}
        
        SceneHandle getHandle() { return m_handle; }
    protected:
        /* Called when added to Engine */
        virtual void build() = 0;

        /* Called when it is on the top of the queue */
        virtual void resume() = 0;

        /* Called each render update */
        virtual void render() = 0;

        /* Called each tick of the game */
        virtual void tick(unsigned long gameTime) = 0;
        ///Ticks are called each loop of the game, updates are called each physics update
        ///Ticks will always be called the same amount or less often than the update call
        /* Called each update of the game */
        virtual void update(float deltaTime) = 0;

        /* Called when it is no longer on the top of the queue */
        virtual void pause() = 0;

        /* Called when the scene is destroyed */
        virtual void destroy() = 0;
    private:
        /* Renderer types */
        DesignRenderer m_designRenderer;
        PrimitiveRenderer m_primitiveRenderer;
        ModelRenderer m_modelRenderer;

        IEngine* m_engine;
        SceneHandle m_handle;
        //std::vector<>
    };
}
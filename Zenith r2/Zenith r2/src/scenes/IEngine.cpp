#include "IEngine.hpp"
#include "core/Zenith.hpp"
#include "debug/Logger.hpp"
#include "IScene.hpp"
#include "util/Maths.hpp"

namespace zen {
    IEngine::IEngine() { }

    int IEngine::start(const char* title /*= "NO TITLE"*/, int x /*= 0*/, int y /*= 0*/, 
                       unsigned int width /*= 640*/, unsigned int height /*= 360*/, WindowFlags windowFlags /*= WindowFlag::WINDOW_DEFAULT*/) {
        int retVal = -1;
        if(!m_running) {
            m_running = true;
            if(zen::init()) {
                return -1;
            }
            m_window = Window(title, x, y, width, height, windowFlags);
            Log::Debug({LogMajorType::EVENT}, "Started game at: ");
            Log::DateTime(true);
            build();
            retVal = run();
            destroy();
            end();
        }
        return retVal;
    }

    void IEngine::pushScene(SceneHandle scene) {
        m_sceneQueue.emplace_back(scene);
        m_scenes[scene].scene->resume();
    }

    void IEngine::popScene(SceneHandle scene) {
        m_scenes[m_sceneQueue.back()].scene->pause();
        m_sceneQueue.pop_back();
    }

    void IEngine::clearScenes() {
        for(auto& sI : m_sceneQueue) {
            m_scenes[sI].scene->pause();
        }
        m_sceneQueue.clear();
    }

    SceneHandle IEngine::registerScene(IScene* scene, SceneType type /*= SceneFlag::DEFAULT_FLAGS*/, bool managedByEngine /*= false*/) {
        SceneRef ref;
        ref.scene = scene;
        ref.type = type;
        ref.managed = managedByEngine;
        //TODO Add renderer initializations
        m_scenes.emplace_back(ref);
        return (SceneHandle)m_scenes.size() - 1;
    }

    // Some helpful constants.
#define DESIRED_FPS m_fpsLimiter.getMaxFPS() // FPS the game is designed to run at
#define MAX_PHYSICS_STEPS (DESIRED_FPS / 10.0f) // Max number of physics steps per frame
#define MS_PER_SECOND 1000.0f // Number of milliseconds in a second
#define DESIRED_FRAMETIME (MS_PER_SECOND / DESIRED_FPS) // The desired frame time per frame
#define MAX_DELTA_TIME 1.0f // Maximum size of deltaTime

    int IEngine::run() {
        m_fpsLimiter.setMaxFPS((m_window.getDisplay().refresh_rate * 2.0f) + 1.0f);
        //TODO Scene tick() call
        // Start timestep
        Uint32 previousTicks = SDL_GetTicks();
        const Uint32 startTime = SDL_GetTicks();
        float accumulation = 0.0f;

        while(m_running) {
            m_fpsLimiter.begin();
            m_gameTime = SDL_GetTicks() - startTime;
            Tick();
            // Calculate the frameTime in milliseconds
            Uint32 newTicks = SDL_GetTicks();
            Uint32 frameTime = newTicks - previousTicks;
            previousTicks = newTicks;
            // Get the total time accumulation
            accumulation = (float)frameTime / DESIRED_FRAMETIME;
            int step = 0;
            while(accumulation > 0.0f && step < MAX_PHYSICS_STEPS) {
                // Get deltatime pass
                float dt = zenmath::min(accumulation, MAX_DELTA_TIME);
                // Update game physics
                Update(dt);

                accumulation -= dt;
                ++step;
            }
            
            if(m_running) {
                Render();
            }
            m_FPS = m_fpsLimiter.end();
        }
        return 0;
    }

    void IEngine::end() {
        clearScenes();
        for(auto& s : m_scenes) {
            //TODO Scene renderer disposal?
            s.scene->destroy();
            if(s.managed) {
                delete s.scene;
            }
            s.scene = nullptr;
        }
        m_scenes.clear();
        //TODO Renderer disposal
        m_window.close();
    }

    void IEngine::Update(float deltaTime) {
        registerEvents();
        update(deltaTime);
        if(!m_sceneQueue.empty()) {
            /* Update the scenes that are queued to be updated */
            int itr = (int)m_sceneQueue.size() - 1;
            SceneRef* refScene = &m_scenes[m_sceneQueue[itr]];
            refScene->scene->update(deltaTime);
            --itr;
            while(itr >= 0 && !(refScene->type & SceneFlag::UPDATE_OVERRIDE)) {
                refScene->scene->update(deltaTime);
                --itr;
                refScene = &m_scenes[m_sceneQueue[itr]];
            }
        }
    }

    void IEngine::Tick() {
        if(!m_sceneQueue.empty()) {
            /* Update the scenes that are queued to be updated */
            int itr = (int)m_sceneQueue.size() - 1;
            SceneRef* refScene = &m_scenes[m_sceneQueue[itr]];
            refScene->scene->tick(m_gameTime);
            --itr;
            while(itr >= 0 && !(refScene->type & SceneFlag::UPDATE_OVERRIDE)) {
                refScene->scene->tick(m_gameTime);
                --itr;
                refScene = &m_scenes[m_sceneQueue[itr]];
            }
        }
    }

    void IEngine::registerEvents() {
        SDL_Event evnt;
        while(SDL_PollEvent(&evnt)) {
            switch(evnt.type) {
            case SDL_QUIT:
                quit();
                break;
            case SDL_MOUSEMOTION:
                //TODO Event Handling
                break;
            case SDL_MOUSEBUTTONDOWN:
                //TODO Event Handling
                break;
            case SDL_MOUSEBUTTONUP:
                //TODO Event Handling
                break;
            case SDL_MOUSEWHEEL:
                //TODO Event Handling
                break;
            case SDL_KEYDOWN:
                //TODO Event Handling
                break;
            case SDL_KEYUP:
                //TODO Event Handling
                break;
            case SDL_CONTROLLERDEVICEADDED:
                //TODO Event Handling
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                //TODO Event Handling
                break;
            case SDL_CONTROLLERAXISMOTION:
                //TODO Event Handling
                break;
            case SDL_CONTROLLERBUTTONUP:
                //TODO Event Handling
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                //TODO Event Handling
                break;
            default:
                break;
            }
        }
    }

    void IEngine::Render() {
        if(!m_sceneQueue.empty()) {
            /* Render the scenes that are queued to be shown */
            int itr = (int)m_sceneQueue.size() - 1;
            SceneRef* refScene = &m_scenes[m_sceneQueue[itr]];
            while(itr >= 0 && !(refScene->type & SceneFlag::RENDER_OVERRIDE)) {
                refScene->scene->render();
                --itr;
                refScene = &m_scenes[m_sceneQueue[itr]];
            }
        }
        m_window.swap();
    }

}
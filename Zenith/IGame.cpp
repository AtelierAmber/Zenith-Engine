#include "IGame.h"
#include "Zenith.h"
#include "IScene.h"

namespace Zenith {
    IGame::IGame() : m_sceneManager(this){}

    IGame::~IGame() {}

    int IGame::start(const char* title /*= "Zenith Game"*/, int x /*= 0*/, 
                     int y /*= 0*/, unsigned int width /*= 1280*/, 
                     unsigned int height /*= 720*/, unsigned int windowFlags /*= 0*/) {
        Core::init();
        if (m_windowManager.createWindow(title, x, y, width, height, windowFlags)) {
            return -1;
        }
        build();
        int retVal = run();
        destroy();
        return retVal;
    }

    int IGame::run() {
        while (m_running) {
            update();
            m_sceneManager.getCurrent()->coreRender();
        }
        return 0;
    }

    void IGame::update() {
        m_inputManager.update(&m_windowManager);
        IUpdate();
        m_sceneManager.getCurrent()->update();
        if (m_windowManager.update()) {
            m_running = false;
        }
    }
}
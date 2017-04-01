#include "IGame.hpp"
#include "core/Zenith.hpp"

namespace zen {
    IGame::IGame() {}

    IGame::~IGame() {}

    int IGame::start(const char* title, int x, int y, int width, int height, WindowFlags flags) {
        zen::init();
        /* Create the window */
        m_window = Window(title, x, y, width, height, flags);
        if(m_window.getContext() == nullptr) {
            return -1;
        }
        /* Build the game */
        build();
        run();
        return 0;
    }

    void IGame::stop() {

    }

    void IGame::addScene(IScene* scene) {

    }

    void IGame::run() {
        m_limiter.setMaxFPS((m_window.getDisplay().refresh_rate * 2.0f) + 1.0f);
        while(m_running) {
            m_limiter.begin();

            m_window.update();
            std::printf("\n%.2f", m_fps);

            m_fps = m_limiter.end();
        }
    }

}
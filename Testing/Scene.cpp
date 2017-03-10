#include "Scene.h"
#include "Game.h"

#include <GL/glew.h>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::build() {
    m_shader = m_renderer.addShader(new StaticShader());
    m_camera.init(m_game->getWindowManager()->getWidth(), m_game->getWindowManager()->getHeight());
    m_renderer.registerView(m_camera.getMatrix());

    /* TESTING */
    //const Zenith::Texture* texture = m_dataLoader.loadImage("assets/wall.png", Zenith::TEX_CLAMP | Zenith::TEX_FILTER_MIPMAP);
    unsigned int id = 0;
    /*if (texture == nullptr) {
        m_logger.log("SCEN", Zenith::LogType::ERROR, "Could not load image assets/wall.png!!");
    }
    else id = texture->id;*/
    m_model = Zenith::Model({ 
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,

        0, 4, 5,
        0, 1, 5,
        1, 5, 6,
        1, 2, 6,
        2, 6, 7,
        2, 3, 7,
        3, 7, 0,
        0, 4, 7
    }, {
        Zenith::Vertex(-0.5f, -0.5f,  0.0f,   0,   0, 255, 255, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f), //0 BL
        Zenith::Vertex(-0.5f,  0.5f,  0.0f,   0, 255,   0, 255, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), //1 TL
        Zenith::Vertex( 0.5f,  0.5f,  0.0f, 255,   0,   0, 255, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), //2 TR
        Zenith::Vertex( 0.5f, -0.5f,  0.0f, 255, 255, 255, 255, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), //3 BR

        Zenith::Vertex(-0.5f, -0.5f,  1.0f, 255,   0,   0, 255, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), //0 BBL
        Zenith::Vertex(-0.5f,  0.5f,  1.0f,   0, 255,   0, 255, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), //1 BTL
        Zenith::Vertex( 0.5f,  0.5f,  1.0f,   0,   0, 255, 255, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), //2 BTR
        Zenith::Vertex( 0.5f, -0.5f,  1.0f, 255, 255, 255, 255, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f) //3 BBR
    }, id);
}

void Scene::enter() {

}

void Scene::render() {
    m_renderer.render(m_shader, &m_model, 0, 0.0f, 0.0f, -3.0f, -m_ticker, 0.0f, m_ticker, 1.0f);
    m_renderer.render(m_shader, &m_model, 0, 1.5f, 1.0f, -3.0f, m_ticker, 0.0f, -m_ticker, 1.0f);
}

void Scene::update() {
    m_camera.update();
    m_ticker += 0.05f;
    if (keyStateIs(Key::r, KeyState::PRESSED) && 
        keyStateIs(Key::Modifier::LSHIFT, KeyState::PRESSED) &&
        keyStateIs(Key::Modifier::LCTRL, KeyState::PRESSED)){
        m_renderer.getShader(m_shader)->reload();
    }
}

void Scene::exit() {

}

void Scene::destroy() {

}

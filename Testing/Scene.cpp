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
    m_model = m_dataLoader.loadOBJ("assets/models/PineTree.zenObj");
    m_pointLight = m_dataLoader.loadOBJ("assets/models/Lantern.zenObj");
}

void Scene::enter() {

}

void Scene::render() {
    m_renderer.render(m_shader, &m_model, Zenith::Transform(glm::vec3(0.0f, 1.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
    //m_renderer.render(m_shader, &m_pointLight, Zenith::Transform(glm::vec3(0.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
}

void Scene::update() {
    m_camera.update();
    m_ticker += 0.005f;

    /* Rotate camera when the mouse is moved */
    m_camera.rotate(glm::vec3(getMouse()->getYRel(), -getMouse()->getXRel(), 0.0f) * -0.1f);

    if (keyStateIs(Key::e, KeyState::PRESSED)) {
        m_camera.rotate(glm::vec3(0.01f, 0.01f, 0.0f));
    }
    if (keyStateIs(Key::q, KeyState::PRESSED)) {
        m_camera.rotate(glm::vec3(-0.01f, -0.01f, 0.0f));
    }

    if (keyStateIs(Key::r, KeyState::PRESSED) && 
        keyStateIs(Key::Modifier::LSHIFT, KeyState::PRESSED) &&
        keyStateIs(Key::Modifier::LCTRL, KeyState::PRESSED)){
        m_renderer.getShader(m_shader)->reload();
    }
    if (keyStateIs(Key::w, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(0.0f, 0.0f, 0.005f));
    }
    if (keyStateIs(Key::s, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(0.0f, 0.0f, -0.005f));
    }
    if (keyStateIs(Key::a, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(-0.005f, 0.0f, 0.0f));
    }
    if (keyStateIs(Key::d, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(0.005f, 0.0f, 0.0f));
    }
    if (keyStateIs(Key::SPACE, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(0.0f, 0.005f, 0.0f));
    }
    if (keyStateIs(Key::Modifier::LCTRL, KeyState::PRESSED)) {
        m_camera.move(glm::vec3(0.0f, -0.005f, 0.0f));
    }
}

void Scene::exit() {

}

void Scene::destroy() {

}

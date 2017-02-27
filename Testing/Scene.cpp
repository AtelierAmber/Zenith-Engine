#include "Scene.h"

#include <GL/glew.h>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::build() {
    m_shader = m_renderer.addShader(new StaticShader());
    std::vector<Zenith::Vertex> vertexes;
    const Zenith::Texture* texture = m_dataLoader.loadImage("assets/wall.png", Zenith::TEX_CLAMP | Zenith::TEX_FILTER_MIPMAP);
    unsigned int id = 0;
    if (texture == nullptr) {
        m_logger.log("SCEN", Zenith::LogType::ERROR, "Could not load image assets/wall.png!!");
    }
    else id = texture->id;
    m_model = Zenith::Model({ 
        0, 1, 2,
        2, 3, 0,
        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        0, 4, 3
    }, {
        Zenith::Vertex(-0.5f, -0.5f,  0.0f, 255, 255, 255, 255, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f), //0 BL
        Zenith::Vertex(-0.5f,  0.5f,  0.0f, 255, 255, 255, 255, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), //1 TL
        Zenith::Vertex( 0.5f,  0.5f,  0.0f, 255, 255, 255, 255, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), //2 TR
        Zenith::Vertex( 0.5f, -0.5f,  0.0f, 255, 255, 255, 255, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), //3 BR
        Zenith::Vertex( 0.0f,  0.0f,  0.5f, 255, 255, 255, 255, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f)  //4 E
    }, id);
}

void Scene::enter() {

}

void Scene::render() {
    m_renderer.render(m_shader, &m_model, 0, 0.0f, 0.5f, 0.0f, 0.0f, m_ticker, 0.0f, 1.0f);
}

void Scene::update() {
    m_ticker += 0.005f;
}

void Scene::exit() {

}

void Scene::destroy() {

}

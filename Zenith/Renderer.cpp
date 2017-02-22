#include "Renderer.h"

#include <GL/glew.h>

namespace Zenith {
    Renderer::Renderer() {
        m_logger.construct("render.log", "RNDR");
        m_batch.begin();
    }

    Renderer::~Renderer() {}

    unsigned int Renderer::addShader(IShaderProgram* program) {
        unsigned int id = m_shaderManager.addProgram(program);
        if (m_compiled) {
            m_logger.log(LogType::WARNING, "Shaders already compiled. Shader " + std::to_string(id) + " will probably not work correctly.");
        }else m_logger.log(LogType::EVENT, "Shader " + std::to_string(id) + " added.");
        return id;
    }

    void Renderer::compile() {
        if (!m_compiled) {

        }
    }

    void Renderer::begin() {
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    void Renderer::render(unsigned int shader, const Model& model) {
        m_models[shader].push_back(model);
    }

    void Renderer::end() {

    }

    void Renderer::dispose() {

    }

    glm::mat4 Renderer::generateTransformMatrix(glm::vec3 position, glm::vec3 rotation, float scale) {
        return glm::mat4();
    }

}
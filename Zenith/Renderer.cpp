#include "Renderer.h"
#include "Primitives.h"
#include "IShaderProgram.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Zenith {
    Renderer::Renderer() {
        m_logger.construct("render.log", "RNDR");
        m_batch.init();
        m_shaderManager.construct(&m_logger);
        glEnable(GL_DEPTH_TEST);
    }

    Renderer::~Renderer() {}

    unsigned int Renderer::addShader(IShaderProgram* program) {
        unsigned int id = m_shaderManager.addProgram(program, m_batch.getVBO(), m_batch.getEBO());
        /*if (m_compiled) {
            m_logger.log(LogType::WARNING, "Shaders already compiled. Shader " + std::to_string(id) + " will probably not work correctly.");
        }else*/ m_logger.log("RNDR", LogType::EVENT, "Shader " + std::to_string(id) + " added.");
        return id;
    }

    Zenith::IShaderProgram* Renderer::getShader(unsigned int programID) {
        return m_shaderManager.getProgram(programID);
    }

    void Renderer::begin() {
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_models.clear();
    }

    void Renderer::render(unsigned int shader, Model* model) {
        m_models[shader].emplace_back(Transform(), model);
    }

    void Renderer::render(unsigned int shader, Model* model, Transform transform) {
        m_models[shader].emplace_back(transform, model);
    }

    void Renderer::render(unsigned int shader, Model* model, Transform transform, std::vector<Transform> objectTransforms) {
        m_models[shader].emplace_back(transform, model, objectTransforms);
    }

    void Renderer::end() {
        /* Itterate through the map */
        for (auto& batch : m_models) {
            m_shaderManager.useProgram(batch.first);
            
            /* For each VAO (map.first) render a new batch */
            m_batch.begin();
            for (unsigned int i = 0; i < m_models[batch.first].size(); ++i) {
                m_batch.add(&m_models[batch.first][i]);
            }
            m_shaderManager.getProgram(batch.first)->loadProjection(*m_viewMatrix);
            m_batch.end();
            m_batch.renderBatch(m_shaderManager.getProgram(batch.first));
            m_shaderManager.endProgram(batch.first);
        }
    }

    void Renderer::dispose() {
        m_shaderManager.dispose();
        m_batch.dispose();
    }
}
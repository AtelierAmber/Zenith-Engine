#include "Renderer.h"
#include "Model.h"
#include "IShaderProgram.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Zenith {
    Renderer::Renderer() {
        m_logger.construct("render.log", "RNDR");
        m_batch.init();
        m_shaderManager.construct(&m_logger);
    }

    Renderer::~Renderer() {}

    unsigned int Renderer::addShader(IShaderProgram* program) {
        unsigned int id = m_shaderManager.addProgram(program, m_batch.getVBO(), m_batch.getEBO());
        /*if (m_compiled) {
            m_logger.log(LogType::WARNING, "Shaders already compiled. Shader " + std::to_string(id) + " will probably not work correctly.");
        }else*/ m_logger.log("RNDR", LogType::EVENT, "Shader " + std::to_string(id) + " added.");
        return id;
    }

    void Renderer::begin() {
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_models.clear();
    }

    void Renderer::render(unsigned int shader, Model* model, float depth) {
        m_models[shader].emplace_back(depth, glm::mat4(1.0f), model);
    }

    void Renderer::render(unsigned int shader, Model* model, float depth, float x, 
        float y, float z, float rotx, float roty, float rotz, float scale) {
        glm::mat4 transform = generateTransformMatrix(glm::vec3(x, y, z), glm::vec3(rotx, roty, rotz), scale);
        m_models[shader].emplace_back(depth, transform, model);
    }

    void Renderer::end() {
        glEnable(GL_DEPTH_TEST);
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

    glm::mat4 Renderer::generateTransformMatrix(glm::vec3 position, glm::vec3 rotation, float scale) const {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        matrix *= scale;
        return matrix;
    }

}
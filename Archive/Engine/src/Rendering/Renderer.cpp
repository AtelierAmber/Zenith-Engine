#include "Rendering/Renderer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace Zenith {
    void Renderer::prepare() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::render(const Entity& entity, StaticShader& shader) {
        glBindVertexArray(entity.getModel().getRawModel().getVaoID());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glm::mat4 transformationMat = entity.transform(entity.getPosition(), entity.getRotation(), entity.getScale());
        shader.loadTransMat(transformationMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity.getModel().getTexture().id);
        glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }
}
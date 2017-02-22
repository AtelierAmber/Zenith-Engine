#include "RenderBatch.h"

#include <GL/glew.h>

namespace Zenith {
    RenderBatch::RenderBatch() {

    }

    RenderBatch::~RenderBatch() { }

    void RenderBatch::init() {
        if (m_vbo == 0) {
            glGenBuffers(1, &m_vbo);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        
    }

    void RenderBatch::begin() {

    }

    void RenderBatch::add(/*@ params*/) {

    }

    void RenderBatch::end() {

    }

    void RenderBatch::renderBatch(int vao) {
        if (!vao || m_renderBatches.empty()) {
            return;
        }
        glBindVertexArray(vao);
        for (std::size_t i = 0; i < m_renderBatches.size(); ++i) {
            glDrawElementsBaseVertex(GL_TRIANGLES, m_renderBatches[i].numIndicies, 
                GL_UNSIGNED_SHORT, 0, m_renderBatches[i].indexOffset);
        }
    }

    void RenderBatch::dispose() {
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
    }

    void RenderBatch::createBatches() {

    }

}
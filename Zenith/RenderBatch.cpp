#include "RenderBatch.h"
#include "Model.h"
#include "Logger.h"

#include <algorithm>
#include <iostream>

#include <GL/glew.h>

namespace Zenith {
    RenderBatch::RenderBatch() {

    }

    RenderBatch::~RenderBatch() { }

    void RenderBatch::init() {
        if (m_vbo == 0) {
            glGenBuffers(1, &m_vbo);
        }
        if (m_ebo == 0) {
            glGenBuffers(1, &m_ebo);
        }
        //! glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    }

    void RenderBatch::begin() {
        m_modelPointers.clear();
        m_renderBatches.clear();
    }

    void RenderBatch::add(DepthModel* model) {
        m_modelPointers.push_back(model);
    }

    void RenderBatch::end() {
        sortBatch(false);
        createBatch();
    }

    void RenderBatch::createBatch() {
        if (m_modelPointers.empty()) {
            return;
        }
        
        /* Vector of all verticies to allow for easy buffer upload */
        std::vector <Vertex> vertices;
        std::vector<unsigned short> indicies;
        /* Initialize the verticies */
        int offset = 0; // current offset

        //Add all the rest of the glyphs
        for (std::size_t c = 0; c < m_modelPointers.size(); ++c) {
            m_renderBatches.emplace_back(offset, m_modelPointers[0]->model->getNumIndicies(), m_modelPointers[0]->model->getTexture(), m_modelPointers[0]->depth);
            for (auto& vert : m_modelPointers[0]->model->getVertices()) {
                vertices.push_back(vert);
            }
            for (auto& ind : m_modelPointers[0]->model->getIndicies()) {
                indicies.push_back(ind);
            }
            offset += m_modelPointers[0]->model->getNumIndicies();
        }

        /* Bind VBO for use */
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        /* Orphan the VBO buffer */
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        /* Upload the data to the VBO */
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

        //////////////////////
        /* Bind EBO for use */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

        /* Orphan the EBO buffer */
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned short), nullptr, GL_DYNAMIC_DRAW);

        /* Upload the data */
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indicies.size() * sizeof(unsigned short), indicies.data());

        GLenum glOK = glGetError();
        if (glOK) {
            std::cerr << "Error " << glOK << " while buffering data! \n";
        }
    }

    void RenderBatch::renderBatch() {
        if ( m_renderBatches.empty()) {
            return;
        }
        GLenum glOK = glGetError();
        if (glOK) {
            std::cerr << "Error " << glOK << " occured before rendering!";
        }

        for (std::size_t i = 0; i < m_renderBatches.size(); ++i) {
            if (m_renderBatches[i].textureID) {
                glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].textureID);
            }
            glDrawElementsBaseVertex(GL_TRIANGLES, m_renderBatches[i].numIndicies, 
                GL_UNSIGNED_SHORT, 0, m_renderBatches[i].indexOffset);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    void RenderBatch::dispose() {
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_ebo) {
            glDeleteBuffers(1, &m_ebo);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /* Sorting functions */
    void RenderBatch::sortBatch(bool backToFront) {
        if (backToFront) {
            std::stable_sort(m_modelPointers.begin(), m_modelPointers.end(), compareBackToFront);
        }
        else {
            std::stable_sort(m_modelPointers.begin(), m_modelPointers.end(), compareFrontToBack);
        }
    }

    bool RenderBatch::compareFrontToBack(DepthModel* a, DepthModel* b) {
        return (a->depth < b->depth);
    }

    bool RenderBatch::compareBackToFront(DepthModel* a, DepthModel* b) {
        return (a->depth > b->depth);
    }
}
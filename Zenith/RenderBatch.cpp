#include "RenderBatch.h"
#include "Logger.h"
#include "IShaderProgram.h"

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

    void RenderBatch::add(TransformedModel* model) {
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

        /* Add the mesh data */
        for (std::size_t c = 0; c < m_modelPointers.size(); ++c) {
            if (m_modelPointers[c]->m_objectTransforms.size() == 0) {
                /* Load model as one mesh */
                unsigned int numIndicies = 0;
                unsigned int newOffset = 0;
                for (auto& obj : m_modelPointers[c]->ptr_model->getObjects()) {
                    for (auto& vert : obj.vertices) {
                        vertices.push_back(vert);
                    }
                    for (auto& face : obj.faces) {
                        indicies.push_back(face.vi_A + newOffset);
                        indicies.push_back(face.vi_B + newOffset);
                        indicies.push_back(face.vi_C + newOffset);
                    }
                    numIndicies += obj.getNumFaces() * 3;
                    newOffset += obj.getNumVerts();
                }

                m_renderBatches.emplace_back(offset, numIndicies, m_modelPointers[c]->ptr_model->getTexture(),
                    m_modelPointers[c]->m_transform.transformMatrix);
                offset += newOffset;
            }
            else {
                /* Load model as multiple meshes, each with different transforms */
                for (unsigned int i = 0; i < m_modelPointers[c]->ptr_model->getObjects().size(); ++i) {
                    auto& obj = m_modelPointers[c]->ptr_model->getObjects()[i];
                    offset += obj.getNumVerts();
                    m_renderBatches.emplace_back(offset, obj.getNumFaces() * 3, m_modelPointers[c]->ptr_model->getTexture(), 
                        m_modelPointers[c]->m_transform.transformMatrix * m_modelPointers[c]->m_objectTransforms[i].transformMatrix);
                    for (auto& vert : obj.vertices) {
                        vertices.push_back(vert);
                    }
                    for (auto& face : obj.faces) {
                        indicies.push_back(face.vi_A);
                        indicies.push_back(face.vi_B);
                        indicies.push_back(face.vi_C);
                    }
                }
            }
        }

        GLenum glOK = glGetError();
        if (glOK) {
            std::cerr << "Error " << glOK << " before buffering data! \n";
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

        glOK = glGetError();
        if (glOK) {
            std::cerr << "Error " << glOK << " while buffering data! \n";
        }
    }

    void RenderBatch::renderBatch(IShaderProgram* shader) {
        if ( m_renderBatches.empty()) {
            return;
        }
        GLenum glOK = glGetError();
        if (glOK) {
            std::cerr << "Error " << glOK << " occured before rendering!";
        }

        for (std::size_t i = 0; i < m_renderBatches.size(); ++i) {
            if (shader->isTextureShader()) {
                glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].textureID);
            }
            shader->loadTransform(m_renderBatches[i].transform);
            glDrawElementsBaseVertex(GL_TRIANGLES, m_renderBatches[i].numIndicies, 
                GL_UNSIGNED_SHORT, 0, m_renderBatches[i].indexOffset);
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

    bool RenderBatch::compareFrontToBack(TransformedModel* a, TransformedModel* b) {
        return (a->m_transform.position.z < b->m_transform.position.z);
    }

    bool RenderBatch::compareBackToFront(TransformedModel* a, TransformedModel* b) {
        return (a->m_transform.position.z > b->m_transform.position.z);
    }
}
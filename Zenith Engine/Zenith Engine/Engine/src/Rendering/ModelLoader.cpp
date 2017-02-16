#include "Rendering/ModelLoader.h"
#include "Logging/Logger.h"

#include <string>

namespace Zenith {
    ModelLoader::ModelLoader() {}

    RawModel ModelLoader::loadToVAO(const float* positions, int numVer, const int* indicies, int numInd) {
        int vaoID = createVAO();
        bindIndiciesBuffer(indicies, numInd);
        storeDataInAttribList(0, positions, numVer);
        unbindVAO();
        RawModel model(vaoID, numInd);
        return model;
    }

    void ModelLoader::dispose() {
        for (auto vao : m_vaos) {
            glDeleteVertexArrays(1, &vao);
        }
        for (auto vbo : m_vbos) {
            glDeleteBuffers(1, &vbo);
        }
    }

    int ModelLoader::createVAO() {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        m_vaos.push_back(vaoID);
        GLint err = glGetError();
        if (err) {
            Log::logError("OpenGL Error during vertex bind: " + std::to_string((int)err));
        }
        return vaoID;
    }

    void ModelLoader::storeDataInAttribList(int attribNum, const float* data, int dataSize) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(float), data, GL_STATIC_DRAW);
        glVertexAttribPointer(attribNum, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_vbos.push_back(vboID);
        GLint err = glGetError();
        if (err) {
            Log::logError("OpenGL Error during buffer bind: " + std::to_string((int)err));
        }
    }

    void ModelLoader::unbindVAO() {
        glBindVertexArray(0);
    }

    void ModelLoader::bindIndiciesBuffer(const int* indicies, int numInd) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInd*sizeof(int), indicies, GL_STATIC_DRAW);
        GLint err = glGetError();
        if (err) {
            Log::logError("OpenGL Error during index bind: " + std::to_string((int)err));
        }
    }

}
#include "Rendering/ModelLoader.h"
#include "Logging/Logger.h"
#include "Rendering/loadpng.h"

namespace Zenith {
    ModelLoader::ModelLoader() {}

    RawModel ModelLoader::loadToVAO(const float* positions, int numVer, const float* textureCoords, const int* indicies, int numInd) {
        int vaoID = createVAO();
        bindIndiciesBuffer(indicies, numInd);
        storeDataInAttribList(0, 3, positions, numVer);
        storeDataInAttribList(1, 2, textureCoords, 2*(numVer/3));
        unbindVAO();
        RawModel model(vaoID, numInd);
        return model;
    }

    int ModelLoader::loadTexture(std::string file) {
        unsigned int id, width, height;
        std::vector<unsigned char> image;
        unsigned int error = lodepng::decode(image, width, height, file);
        if (error) {
            Log::logError("Could not load " + file + " to stream. Error: " + std::string(lodepng_error_text(error)));
            return error;
        }
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
        glGenerateMipmap(GL_TEXTURE_2D);
        GLint err = glGetError();
        if (err) {
            Log::logError("Failed to load texture: " + file + " Open GL error: " + std::to_string(err));
        }
        m_textures.push_back(id);
        glBindTexture(GL_TEXTURE_2D, 0);
        return id;
    }

    void ModelLoader::dispose() {
        for (auto vao : m_vaos) {
            glDeleteVertexArrays(1, &vao);
        }
        for (auto vbo : m_vbos) {
            glDeleteBuffers(1, &vbo);
        }
        for (auto tex : m_textures) {
            glDeleteTextures(1, &tex);
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

    void ModelLoader::storeDataInAttribList(int attribNum, int coordSize, const float* data, int dataSize) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(float), data, GL_STATIC_DRAW);
        glVertexAttribPointer(attribNum, coordSize, GL_FLOAT, GL_FALSE, 0, 0);
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
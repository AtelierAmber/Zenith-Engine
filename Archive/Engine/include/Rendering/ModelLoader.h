#pragma once
#include "TexturedModel.h"
#include <GL/glew.h>

#include <string>
#include <vector>

namespace Zenith {
    class ModelLoader {
    public:
        ModelLoader();

        RawModel loadToVAO(const float* positions, int numVer, const float* textureCoords, const int* indicies, int numInd);
		int loadTexture(std::string file);

        void dispose();

    private:
        int createVAO();
        void storeDataInAttribList(int attribNum, int coordSize, const float* data, int dataSize);
        void unbindVAO();
        void bindIndiciesBuffer(const int* indicies, int numInd);

        std::vector<GLuint> m_vaos;
        std::vector<GLuint> m_vbos;
        std::vector<GLuint> m_textures;
    };
}
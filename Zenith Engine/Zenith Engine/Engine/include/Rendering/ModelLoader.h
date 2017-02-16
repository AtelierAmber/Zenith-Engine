#pragma once
#include "RawModel.h"
#include <GL/glew.h>

#include <vector>

namespace Zenith {
    class ModelLoader {
    public:
        ModelLoader();

        RawModel loadToVAO(const float* positions, int numVer, const int* indicies, int numInd);
        void dispose();

    private:
        int createVAO();
        void storeDataInAttribList(int attribNum, const float* data, int dataSize);
        void unbindVAO();
        void bindIndiciesBuffer(const int* indicies, int numInd);

        std::vector<GLuint> m_vaos;
        std::vector<GLuint> m_vbos;
    };
}
#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace Zenith {
    class RawModel {
    public:
        RawModel(int id = -1, int vertCount = -1) : vaoID(id), vertexCount(vertCount) { }

        int getVaoID() const { return vaoID; }
        int getVertexCount() const { return vertexCount; }

    private:
        int vaoID;
        int vertexCount;
    };
}
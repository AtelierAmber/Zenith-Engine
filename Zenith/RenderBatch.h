#pragma once
#include "Vertex.h"

#include <vector>

namespace Zenith {
    struct Mesh {
        Mesh(unsigned int offset, unsigned int NumIndicies, unsigned int texture) :
            indexOffset(offset), numIndicies(NumIndicies), textureID(texture){}
        unsigned int indexOffset;
        unsigned int numIndicies;
        unsigned int textureID;
    };

    class RenderBatch {
    public:
        RenderBatch();
        ~RenderBatch();

        void init();
        void begin();

        void add(/*@ params*/);

        void end();

        void renderBatch(int vao);

        void dispose();

    private:
        unsigned int m_vbo;
        void createBatches();
        std::vector<Mesh> m_renderBatches;
    };
}
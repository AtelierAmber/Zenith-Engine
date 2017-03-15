#pragma once
#include <vector>
#include "Primitives.h"

#include <glm/glm.hpp>

namespace Zenith {
    class Logger;
    class IShaderProgram;

    class RenderBatch {
    public:
        RenderBatch();
        ~RenderBatch();

        void init();
        void begin();

        void add(TransformedModel* model);

        void end();

        void renderBatch(IShaderProgram* shader);

        void dispose();

        const unsigned int& getVBO() { return m_vbo; }
        const unsigned int& getEBO() { return m_ebo; }

    private:
        void createBatch();

        void sortBatch(bool frontToBack);
        static bool compareFrontToBack(TransformedModel* a, TransformedModel* b);
        static bool compareBackToFront(TransformedModel* a, TransformedModel* b);

        Logger* m_logger;
        unsigned int m_vbo, m_ebo;
        /* Vector of pointers to the meshes to allow for quick sorting */
        std::vector<TransformedModel*> m_modelPointers;
        std::vector<Mesh> m_renderBatches;
    };
}
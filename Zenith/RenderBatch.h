#pragma once
#include <vector>

#include <glm/glm.hpp>

namespace Zenith {
    class Logger;
    class Model;
    class IShaderProgram;
    struct DepthModel {
        DepthModel(float Depth, glm::mat4 Transform, Model* modelPoint) : depth(Depth), model(modelPoint), transform(Transform) {}
        float depth;
        glm::mat4 transform;
        Model* model;
    };

    struct Mesh {
        Mesh(unsigned int offset, unsigned int NumIndicies, unsigned int texture, 
            float Depth, glm::mat4 Transform) :
            indexOffset(offset), numIndicies(NumIndicies), textureID(texture), 
            depth(Depth), transform(Transform) {}
        glm::mat4 transform;
        unsigned int indexOffset;
        unsigned int numIndicies;
        unsigned int textureID;
        float depth;
    };

    class RenderBatch {
    public:
        RenderBatch();
        ~RenderBatch();

        void init();
        void begin();

        void add(DepthModel* model);

        void end();

        void renderBatch(IShaderProgram* shader);

        void dispose();

        const unsigned int& getVBO() { return m_vbo; }
        const unsigned int& getEBO() { return m_ebo; }

    private:
        void createBatch();

        void sortBatch(bool frontToBack);
        static bool compareFrontToBack(DepthModel* a, DepthModel* b);
        static bool compareBackToFront(DepthModel* a, DepthModel* b);

        Logger* m_logger;
        unsigned int m_vbo, m_ebo;
        /* Vector of pointers to the meshes to allow for quick sorting */
        std::vector<DepthModel*> m_modelPointers;
        std::vector<Mesh> m_renderBatches;
    };
}
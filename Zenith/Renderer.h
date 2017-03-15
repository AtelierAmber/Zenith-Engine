#pragma once
#include "Logger.h"
#include "ShaderManager.h"
#include "RenderBatch.h"

#include <glm/glm.hpp>

#include <unordered_map>

namespace Zenith {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        /* Returns the index of the shader 
         * Used for rendering 
         * CALL BEFORE COMPILE */
        unsigned int addShader(IShaderProgram* program);

        IShaderProgram* getShader(unsigned int programID);

        /* Compiles resources such as shaders 
        void compile();*/

        /* Starts the batch queueing and render calls */
        void begin();

        /* Renders an entity object 
         * //TODO: Seperate into multiple render variants
         * Generates transformation matrix automatically */
        void render(unsigned int shader, Model* model);
        void render(unsigned int shader, Model* model, Transform transform);
        void render(unsigned int shader, Model* model, Transform transform, 
            std::vector<Transform> objectTransforms);

        /* Finalizes all render() calls and stores them
         * in a single buffer to be rendered on screen */
        void end();

        /* Cleans up shaders and rendering */
        void dispose();

        void registerView(glm::mat4* matrix) { m_viewMatrix = matrix; }

    private:

        /* Pointer to the camera matrix
         * Updates whenever the camera updates, it is a pointer after all */
        glm::mat4* m_viewMatrix;
        /* Use map to map shader index to vector of models to render */
        unsigned int m_currentShader = 0;
        std::unordered_map<unsigned int, std::vector<TransformedModel>> m_models;

        bool m_compiled = false;
        Logger m_logger;
        ShaderManager m_shaderManager;
        RenderBatch m_batch;
    };
}
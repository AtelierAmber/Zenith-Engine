#pragma once
#include "Logger.h"
#include "ShaderManager.h"
#include "RenderBatch.h"
#include "Model.h"

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

        /* Compiles resources such as shaders */
        void compile();

        /* Starts the batch queueing and render calls */
        void begin();

        /* Renders an entity object 
         * //TODO: Seperate into multiple render variants
         * Generates transformation matrix automatically */
        void render(unsigned int shader, const Model& model);

        /* Finalizes all render() calls and stores them
         * in a single buffer to be rendered on screen */
        void end();

        /* Cleans up shaders and rendering */
        void dispose();

    private:
        glm::mat4 generateTransformMatrix(glm::vec3 position, glm::vec3 rotation, float scale);

        unsigned int m_currentShader = 0;
        std::unordered_map<int, std::vector<const Model&>> m_models;

        bool m_compiled = false;
        Logger m_logger;
        ShaderManager m_shaderManager;
        RenderBatch m_batch;
    };
}
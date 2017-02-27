#pragma once

#include "Logger.h"

#include <glm/glm.hpp>

namespace Zenith {

    class IShaderProgram {
    friend class ShaderManager;
    public:
        IShaderProgram();
        ~IShaderProgram();

        void reload();
        const unsigned int getVAO() { return m_vao; }

        void loadTransform(const glm::mat4& mat);

    protected:
        /* Use to load shader files 
         * Construct must include: 
         * loadShader calls */
        virtual void construct() = 0;
        void setTransform(const char* name);
        /* Can be overloaded if a custom Vertex type is needed */
        virtual void setupVAO(const unsigned int& vbo, const unsigned int& ebo);
        void setVertexAttribute(unsigned int attribNum, int numComponents, 
            unsigned int type, bool normalized, int size, const void* offset);
        unsigned int loadShader(const char* filename, int type);

        /* Use to bind VAO attributes to shader variables */
        virtual void bindAttributes() = 0;
        void bindAttribute(int index, const char* name);

        virtual void loadUniforms() = 0;

        int getUniformLocation(const char* name);
        void loadIntU(int location, int value) const;
        void loadFloatU(int location, float value) const;
        void loadVecU(int location, glm::vec3 vec) const;
        void loadBoolU(int location, bool value) const;
        void loadMatU(int location, glm::mat4 mat) const;

    private:
        void link();

        void dispose();

        void use();
        void end();

        Logger* m_shaderLog = nullptr;

        const char* m_transformLoc;
        unsigned int m_vao = 0;
        unsigned int m_numAttribs = 0;
        unsigned int m_id = 0;
        unsigned int m_vertexID = 0;
        unsigned int m_fragmentID = 0;
    };
}
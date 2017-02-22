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

    protected:
        /* Use to load shader files */
        virtual void construct() = 0;
        unsigned int loadShader(const char* filename, int type);

        /* Use to bind VAO attributes to shader variables */
        virtual void bindAttributes() = 0;
        void bindAttribute(int attrib, const char* name);

        virtual void loadUniforms() = 0;
        int getUniformLocation(const char* name);
        void loadFloatU(int location, float value) const;
        void loadVecU(int location, glm::vec3 vec) const;
        void loadBoolU(int location, bool value) const;
        void loadMatU(int location, glm::mat4 mat) const;

    private:

        int compile();

        void dispose();

        void use();
        void end();

        Logger* m_shaderLog = nullptr;

        unsigned int m_numAttribs = 0;
        unsigned int m_id;
        unsigned int m_vertexID = 0;
        unsigned int m_fragmentID = 0;
    };
}
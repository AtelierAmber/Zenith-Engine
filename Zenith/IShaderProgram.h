#pragma once

#include "Logger.h"

#include <glm/glm.hpp>
#include <vector>

namespace Zenith {

    enum class UniformType {
        UNIFORM_INT,
        UNIFORM_FLOAT,
        UNIFORM_VEC,
        UNIFORM_BOOL,
        UNIFORM_MAT
    };

    struct GLUniform {
        GLUniform(const char* Name, void* Value_ptr, UniformType Type) : 
            name(Name), value_ptr(Value_ptr), type(Type) {}
        GLUniform(int Location, void* Value_ptr, UniformType Type) :
            location(Location), type(Type) {}
        const char* name;
        int location;
        UniformType type;
        void* value_ptr = nullptr;
    };

    class IShaderProgram {
    friend class ShaderManager;
    public:
        IShaderProgram(bool hasMaterial, bool hasTexture);
        ~IShaderProgram();

        void reload();
        const unsigned int getVAO() { return m_vao; }

        void loadTransform(const glm::mat4& mat);
        void loadProjection(const glm::mat4& mat);

        bool isMaterialShader() { return m_material; }
        bool isTextureShader() { return m_texture; }

        unsigned int addUniform(const char* name, void* value_ptr, UniformType type);
        void editUniform(unsigned int uniformIndex, void* newValue_ptr, UniformType type);
    protected:
        /* Use to load shader files 
         * Construct must include: 
         * loadShader calls
         * single call to both setTransform and setProjection 
         * and calls to adding uniforms*/
        virtual void construct() = 0;
        void setTransform(const char* name);
        void setProjection(const char* name);
        /* Can be overloaded if a custom Vertex type is needed */
        virtual void setupVAO(const unsigned int& vbo, const unsigned int& ebo);
        void setVertexAttribute(unsigned int attribNum, int numComponents, 
            unsigned int type, bool normalized, int size, const void* offset);
        unsigned int loadShader(const char* filename, int type);

        /* Use to bind VAO attributes to shader variables */
        virtual void bindAttributes() = 0;
        void bindAttribute(int index, const char* name);

        void loadUniforms();
        virtual void loadStaticUniforms() = 0;

        int getUniformLocation(const char* name);
        void loadIntU(int location, int value) const;
        void loadFloatU(int location, float value) const;
        void loadVecU(int location, glm::vec3 vec) const;
        void loadVecU(int location, glm::vec4 vec) const;
        void loadBoolU(int location, bool value) const;
        void loadMatU(int location, glm::mat4 mat) const;

    private:

        void updateUniforms();

        void link();

        void dispose();

        void use();
        void end();

        bool m_material, m_texture;

        Logger* m_shaderLog = nullptr;

        bool m_uniformsUpdated = false;
        bool m_needsUpdate = false;
        std::vector<GLUniform> m_uniforms;

        const char* m_transformLoc;
        const char* m_projectionLoc;
        unsigned int m_vao = 0;
        unsigned int m_numAttribs = 0;
        unsigned int m_id = 0;
        unsigned int m_vertexID = 0;
        unsigned int m_fragmentID = 0;
    };
}
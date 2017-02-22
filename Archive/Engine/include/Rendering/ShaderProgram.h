#pragma once
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Zenith {
    class ShaderProgram {
    public:
        ShaderProgram(std::string vertexFile, std::string fragmentFile);
        void compile();

        void start();
        void end();
        void dispose();
    protected:
        virtual void bindAttributes() = 0;
        void bindAttribute(int attribute, std::string name);

        int getUniformLocation(const char* name) const;
        virtual void getAllUniformLocations() = 0;
        void loadFloatU(int location, float value) const;
        void loadVecU(int location, glm::vec3 vec) const;
        void loadBoolU(int location, bool value) const;
        void loadMatU(int location, glm::mat4 mat) const;
    private:
        GLuint loadShader(std::string fileName, int type);
        std::string m_vertexFile;
        std::string m_fragmentFile;
        GLuint m_programID;
        GLuint m_vertexID;
        GLuint m_fragmentID;
    };
}
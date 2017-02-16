#pragma once
#include <vector>

#include <GL/glew.h>

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
    private:
        GLuint loadShader(std::string fileName, int type);
        std::string m_vertexFile;
        std::string m_fragmentFile;
        GLuint m_programID;
        GLuint m_vertexID;
        GLuint m_fragmentID;
    };
}
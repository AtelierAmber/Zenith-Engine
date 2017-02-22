#include "Rendering/ShaderProgram.h"
#include "Logging/Logger.h"

#include <fstream>

namespace Zenith {

    ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile) :
        m_vertexFile(vertexFile), m_fragmentFile(fragmentFile){
        
    }


    void ShaderProgram::compile() {
        m_vertexID = loadShader(m_vertexFile, GL_VERTEX_SHADER);
        m_fragmentID = loadShader(m_fragmentFile, GL_FRAGMENT_SHADER);
        m_programID = glCreateProgram();
        glAttachShader(m_programID, m_vertexID);
        glAttachShader(m_programID, m_fragmentID);
        bindAttributes();
        glLinkProgram(m_programID);
        glValidateProgram(m_programID);
        GLenum glOK = glGetError();
        if (glOK != GL_NO_ERROR) {
            Log::logError("GL error during shader init: " + std::to_string(glOK));
        }
    }

    void ShaderProgram::start() {
        glUseProgram(m_programID);
    }

    void ShaderProgram::end() {
        glUseProgram(0);
    }

    void ShaderProgram::dispose() {
        end();
        glDetachShader(m_programID, m_vertexID);
        glDetachShader(m_programID, m_fragmentID);
        glDeleteShader(m_vertexID);
        glDeleteShader(m_fragmentID);
        glDeleteProgram(m_programID);
    }

    void ShaderProgram::bindAttribute(int attribute, std::string name) {
        glBindAttribLocation(m_programID, attribute, name.c_str());
    }

    int ShaderProgram::getUniformLocation(const char* name) const {
        return glGetUniformLocation(m_programID, name);
    }

    void ShaderProgram::loadFloatU(int location, float value) const {
        glUniform1f(location, value);
    }

    void ShaderProgram::loadVecU(int location, glm::vec3 vec) const {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void ShaderProgram::loadBoolU(int location, bool value) const {
        glUniform1f(location, (value)?1:0);
    }

    void ShaderProgram::loadMatU(int location, glm::mat4 mat) const {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    GLuint ShaderProgram::loadShader(std::string fileName, int type) {
        std::ifstream file;
        file.open(fileName);
        if (file.fail()) {
            Log::logError("Shader: " + fileName + " could not be opened");
            return -1;
        }
        std::string line;
        std::string source;
        while (std::getline(file, line)) {
            source += line + "\n";
        }
        const char* shaderSource = source.c_str();
        file.close();
        GLuint shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &shaderSource, NULL);
        glCompileShader(shaderID);
        GLint shader_ok;
        GLchar infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shader_ok);
        if (!shader_ok) {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            Log::logError("Could not compile shader: " + fileName + "\n\t\t\t" + infoLog);
        }
        return shaderID;
    }
}
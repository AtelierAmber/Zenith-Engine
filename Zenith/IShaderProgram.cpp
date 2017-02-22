#include "IShaderProgram.h"

#include <string>
#include <fstream>
#include <GL/glew.h>

namespace Zenith {

    IShaderProgram::IShaderProgram() {}

    IShaderProgram::~IShaderProgram() {}

    void IShaderProgram::reload() {
        
    }

    unsigned int IShaderProgram::loadShader(const char* filename, int type) {
        std::ifstream file;
        file.open(filename);
        if (file.fail()) {
            m_shaderLog->log(LogType::ERROR, "Shader: " + std::string(filename) + " could not be opened!");
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
        switch (type) {
        case GL_VERTEX_SHADER:
            m_vertexID = shaderID;
            break;
        case GL_GEOMETRY_SHADER:

            break;
        case GL_FRAGMENT_SHADER:
            m_fragmentID = shaderID;
            break;
        default:
            m_shaderLog->log(LogType::WARNING, "Unknown shader type: " + std::to_string(type) + ". Shader may not have loaded correctly!");
            break;
        }
        if (!shaderID) {
            m_shaderLog->log(LogType::ERROR, "Could not create shader: " + std::string(filename) + "!", glGetError());
        }
        glShaderSource(shaderID, 1, &shaderSource, NULL);
        glCompileShader(shaderID);
        GLint shader_ok;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shader_ok);
        if (!shader_ok) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            m_shaderLog->log(LogType::ERROR, "Could not compile shader: " + std::string(filename) + "!\n\t\t\t" + infoLog);
        }
        m_shaderLog->log(LogType::EVENT, "Shader ");
        return shaderID;
    }

    void IShaderProgram::bindAttribute(int attrib, const char* name) {
        glBindAttribLocation(m_id, attrib, name);
        ++m_numAttribs;
    }

    int IShaderProgram::getUniformLocation(const char* name) {
        return glGetUniformLocation(m_id, name);
    }

    void IShaderProgram::loadFloatU(int location, float value) const {
        glUniform1f(location, value);
    }

    void IShaderProgram::loadVecU(int location, glm::vec3 vec) const {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void IShaderProgram::loadBoolU(int location, bool value) const {
        glUniform1f(location, (value)?1:0);
    }

    void IShaderProgram::loadMatU(int location, glm::mat4 mat) const {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    int IShaderProgram::link() {
        bindAttributes();
        m_id = glCreateProgram();
        if (m_vertexID) {
            glAttachShader(m_id, m_vertexID);
        }
        else m_shaderLog->log(LogType::WARNING, std::to_string(m_id) + "'s vertex shader not loaded!");
        if (m_fragmentID) {
            glAttachShader(m_id, m_fragmentID);
        }
        else m_shaderLog->log(LogType::WARNING, std::to_string(m_id) + "'s fragment shader not loaded!");
        glLinkProgram(m_id);
        glValidateProgram(m_id);
        GLint glOK;
        glGetProgramiv(m_id, GL_LINK_STATUS, (int *)&glOK);
        if (glOK == GL_FALSE){
            GLchar infoLog[512];
            glGetProgramInfoLog(m_id, 512, NULL, infoLog);
            m_shaderLog->log(LogType::ERROR, "Program " + std::to_string(m_id) + " could not be validated!\n\t\t\t" + infoLog, glOK);
            glDeleteProgram(m_id);
        }
        glDetachShader(m_id, m_vertexID);
        glDetachShader(m_id, m_fragmentID);
        glDeleteShader(m_vertexID);
        glDeleteShader(m_fragmentID);
        m_shaderLog->log(LogType::EVENT, "Program " + std::to_string(m_id) + " compiled.");
    }

    void IShaderProgram::dispose() {
        end();
        if (m_id) {
            glDeleteProgram(m_id);
            m_id = 0;
        }
        m_numAttribs = 0;
    }

    void IShaderProgram::use() {
        glUseProgram(m_id);
        /* Enable all attributes */
        for (int i = 0; i < m_numAttribs; ++i) {
            glEnableVertexAttribArray(i);
        }
    }

    void IShaderProgram::end() {
        glUseProgram(0);
        for (int i = 0; i < m_numAttribs; i++) {
            glDisableVertexAttribArray(i);
        }
    }

}
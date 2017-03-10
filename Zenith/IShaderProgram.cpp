#include "IShaderProgram.h"
#include "Vertex.h"

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

namespace Zenith {

    IShaderProgram::IShaderProgram(bool hasMaterial, bool hasTexture) : 
        m_material(hasMaterial), m_texture(hasTexture){
        m_id = glCreateProgram();
    }

    IShaderProgram::~IShaderProgram() {}

    void IShaderProgram::reload() {
        if (m_vertexName != "NO_FILE_NAME") {
            loadShader(m_vertexName.c_str(), GL_VERTEX_SHADER);
        }
        if (m_fragmentName != "NO_FILE_NAME") {
            loadShader(m_fragmentName.c_str(), GL_FRAGMENT_SHADER);
        }
        link();
        updateUniforms();
    }

    void IShaderProgram::loadTransform(const glm::mat4& mat) {
        if (m_transformLoc != 0) {
            glUniformMatrix4fv(getUniformLocation(m_transformLoc), 1, GL_FALSE, &mat[0][0]);
        }
    }
    void IShaderProgram::loadProjection(const glm::mat4& mat) {
        if (m_transformLoc != 0) {
            glUniformMatrix4fv(getUniformLocation(m_projectionLoc), 1, GL_FALSE, &mat[0][0]);
        }
    }

    void IShaderProgram::setTransform(const char* name) {
        m_transformLoc = name;
    }
    void IShaderProgram::setProjection(const char* name) {
        m_projectionLoc = name;
    }

    void IShaderProgram::setupVAO(const unsigned int& vbo, const unsigned int& ebo) {
        if (m_vao == 0) {
            glGenVertexArrays(1, &m_vao);
        }
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        setVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        setVertexAttribute(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        setVertexAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        setVertexAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glBindVertexArray(0);
    }

    void IShaderProgram::setVertexAttribute(unsigned int attribNum, int numComponents,
        unsigned int type, bool normalized, int size, const void* offset) {
        glVertexAttribPointer(attribNum, numComponents, type, normalized, size, offset);
        GLenum glOK = glGetError();
        if (glOK) {
            m_shaderLog->log("SHDR", LogType::ERROR, "Could not set vertex attrib pointer!", glOK);
        }
        glOK = glGetError();
        if (glOK) {
            m_shaderLog->log("SHDR", LogType::ERROR, "Error while setting vertex attribute " + std::to_string(attribNum), glOK);
        }
    }

    unsigned int IShaderProgram::loadShader(const char* filename, int type) {
        std::ifstream file;
        file.open(filename);
        if (file.fail()) {
            m_shaderLog->log("SHDR", LogType::ERROR, "Shader: " + std::string(filename) + " could not be opened!");
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
            m_vertexName = filename;
            break;
        case GL_GEOMETRY_SHADER:

            break;
        case GL_FRAGMENT_SHADER:
            m_fragmentID = shaderID;
            m_fragmentName = filename;
            break;
        default:
            m_shaderLog->log("SHDR", LogType::WARNING, "Unknown shader type: " + std::to_string(type) + ". Shader may not have loaded correctly!");
            break;
        }
        if (!shaderID) {
            m_shaderLog->log("SHDR", LogType::ERROR, "Could not create shader: " + std::string(filename) + "!", glGetError());
        }
        glShaderSource(shaderID, 1, &shaderSource, NULL);
        glCompileShader(shaderID);
        GLint shader_ok;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shader_ok);
        if (!shader_ok) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            m_shaderLog->log("SHDR", LogType::ERROR, "Could not compile shader: " + std::string(filename) + "!\n\t\t\t" + infoLog);
        }
        m_shaderLog->log("SHDR", LogType::EVENT, "Shader " + std::string(filename) + " finished compiling.");
        return shaderID;
    }

    /* Bind an attribute (position, color, etc.) to a layout location in the shader. 
     * Needs to be called before compiling and linking and in sequential order */
    void IShaderProgram::bindAttribute(int index, const char* name) {
        glBindAttribLocation(m_id, index, name);
        GLenum glOK = glGetError();
        if (glOK) {
            m_shaderLog->log("SHDR", LogType::WARNING, "Error while binding attribute " + std::string(name), glOK);
        }
        ++m_numAttribs;
    }

    unsigned int IShaderProgram::addUniform(const char* name, void* value_ptr, UniformType type) {
        for (int i = 0; i < m_uniforms.size(); ++i) {
            if (m_uniforms[i].name == name) {
                m_uniforms[i].type = type;
                m_uniforms[i].value_ptr = value_ptr;
                return i;
            }
        }
        if (!m_uniformsUpdated) {
            m_uniforms.emplace_back(name, value_ptr, type);
        }else m_uniforms.emplace_back(getUniformLocation(name), value_ptr, type);
        GLenum glOK = glGetError();
        if (glOK) {
            m_shaderLog->log("SHDR", LogType::WARNING, "Error while adding uniform " + std::string(name), glOK);
        }
        return (unsigned int)m_uniforms.size() - 1;
    }

    void IShaderProgram::editUniform(unsigned int uniformIndex, void* newValue_ptr, UniformType type) {
        if (uniformIndex > m_uniforms.size()) {
            m_shaderLog->log("SHDR", LogType::WARNING, "Tried to modify uniform that does not exist!", uniformIndex);
            return;
        }
        m_uniforms[uniformIndex].type = type;
        m_uniforms[uniformIndex].value_ptr = newValue_ptr;
    }

    void IShaderProgram::loadUniforms() {
        for (auto& uni : m_uniforms) {
            switch (uni.type) {
            case UniformType::UNIFORM_INT:
                loadIntU(uni.location, *(static_cast<int*>(uni.value_ptr)));
                break;
            case UniformType::UNIFORM_FLOAT:
                loadFloatU(uni.location, *(static_cast<float*>(uni.value_ptr)));
                break;
            case UniformType::UNIFORM_VEC:
                loadVecU(uni.location, *(static_cast<glm::vec3*>(uni.value_ptr)));
                break;
            case UniformType::UNIFORM_BOOL:
                loadBoolU(uni.location, *(static_cast<bool*>(uni.value_ptr)));
                break;
            case UniformType::UNIFORM_MAT:
                loadMatU(uni.location, *(static_cast<glm::mat4*>(uni.value_ptr)));
                break;
            default:
                break;
            }
        }
    }

    int IShaderProgram::getUniformLocation(const char* name) {
        return glGetUniformLocation(m_id, name);
    }
    void IShaderProgram::loadIntU(int location, int value) const {
        glUniform1i(location, value);
    }
    void IShaderProgram::loadFloatU(int location, float value) const {
        glUniform1f(location, value);
    }
    void IShaderProgram::loadVecU(int location, glm::vec3 vec) const {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }
    void IShaderProgram::loadVecU(int location, glm::vec4 vec) const {
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }
    void IShaderProgram::loadBoolU(int location, bool value) const {
        glUniform1i(location, (value)?1:0);
    }
    void IShaderProgram::loadMatU(int location, glm::mat4 mat) const {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void IShaderProgram::updateUniforms() {
        use();
        loadStaticUniforms();
        for (auto& uni : m_uniforms){
            uni.location = getUniformLocation(uni.name);
        }
        m_uniformsUpdated = true;
        end();
    }

    void IShaderProgram::link() {
        if (m_vertexID) {
            glAttachShader(m_id, m_vertexID);
        }
        else m_shaderLog->log("SHDR", LogType::WARNING, std::to_string(m_id) + "'s vertex shader not loaded!");
        if (m_fragmentID) {
            glAttachShader(m_id, m_fragmentID);
        }
        else m_shaderLog->log("SHDR", LogType::WARNING, std::to_string(m_id) + "'s fragment shader not loaded!");
        glLinkProgram(m_id);
        glValidateProgram(m_id);
        GLint glOK;
        glGetProgramiv(m_id, GL_LINK_STATUS, (int *)&glOK);
        if (glOK == GL_FALSE){
            GLchar infoLog[512];
            glGetProgramInfoLog(m_id, 512, NULL, infoLog);
            m_shaderLog->log("SHDR", LogType::ERROR, "Program " + std::to_string(m_id) + " could not be validated!\n\t\t\t" + infoLog, glOK);
            glDeleteProgram(m_id);
        }
        glDetachShader(m_id, m_vertexID);
        glDetachShader(m_id, m_fragmentID);
        glDeleteShader(m_vertexID);
        glDeleteShader(m_fragmentID);
        m_shaderLog->log("SHDR", LogType::EVENT, "Program " + std::to_string(m_id) + " compiled.");
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
        glBindVertexArray(m_vao);
        /* Enable all attributes */
        for (unsigned int i = 0; i < m_numAttribs; ++i) {
            glEnableVertexAttribArray(i);
        }
    }

    void IShaderProgram::end() {
        glUseProgram(0);
        glBindVertexArray(0);
        for (unsigned int i = 0; i < m_numAttribs; i++) {
            glDisableVertexAttribArray(i);
        }
    }
}
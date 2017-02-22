#include "Rendering/StaticShader.h"

namespace Zenith {
    StaticShader::StaticShader():
        ShaderProgram(VERTEX_FILE, FRAGMENT_FILE){

    }

    void StaticShader::loadTransMat(glm::mat4 mat) {
        loadMatU(m_transMatLoc, mat);
    }

    void StaticShader::bindAttributes() {
        bindAttribute(0, "position");
        bindAttribute(1, "textureCoords");
    }

    void StaticShader::getAllUniformLocations() {
        m_transMatLoc = getUniformLocation("transMat");
    }
}
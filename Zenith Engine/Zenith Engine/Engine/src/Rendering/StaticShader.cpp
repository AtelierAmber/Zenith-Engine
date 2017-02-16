#include "Rendering/StaticShader.h"

namespace Zenith {
    StaticShader::StaticShader():
        ShaderProgram(VERTEX_FILE, FRAGMENT_FILE){

    }

    void StaticShader::bindAttributes() {
        bindAttribute(0, "position");
    }
}
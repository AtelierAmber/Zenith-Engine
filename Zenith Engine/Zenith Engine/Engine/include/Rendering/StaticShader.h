#pragma once
#include "ShaderProgram.h"

namespace Zenith {
    const std::string VERTEX_FILE = "shader_default/vertex.vert";
    const std::string FRAGMENT_FILE = "shader_default/fragment.frag";

    class StaticShader :
        public ShaderProgram {
    public:
        StaticShader();

    protected:
        void bindAttributes() override;
    };
}
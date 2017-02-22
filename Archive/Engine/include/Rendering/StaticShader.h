#pragma once
#include "ShaderProgram.h"

namespace Zenith {
    const std::string VERTEX_FILE = "shader_default/vertex.vert";
    const std::string FRAGMENT_FILE = "shader_default/fragment.frag";

    class StaticShader :
        public ShaderProgram {
    public:
        StaticShader();

        void loadTransMat(glm::mat4 mat);

    protected:
        void bindAttributes() override;
        virtual void getAllUniformLocations() override;

    private:
        int m_transMatLoc = 0;
    };
}
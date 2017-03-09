#include "MaterialShader.h"

#include <GL/glew.h>

MaterialShader::MaterialShader() : IShaderProgram(true, true){}

MaterialShader::~MaterialShader(){}

void MaterialShader::construct() {
    loadShader("./shaders/static.vert", GL_VERTEX_SHADER);
    loadShader("./shaders/static.frag", GL_FRAGMENT_SHADER);
    setTransform("transform");
    setProjection("projection");
    addUniform("tex", 0, Zenith::UniformType::UNIFORM_INT);
}

void MaterialShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "color");
    bindAttribute(2, "uv");
    bindAttribute(3, "normal");
}

void MaterialShader::loadStaticUniforms() {
    
}

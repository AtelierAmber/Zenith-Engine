#include "StaticShader.h"

#include <GL/glew.h>

StaticShader::StaticShader() : IShaderProgram(false, true){

}

StaticShader::~StaticShader(){

}

void StaticShader::construct() {
    loadShader("./shaders/static.vert", GL_VERTEX_SHADER);
    loadShader("./shaders/static.frag", GL_FRAGMENT_SHADER);
    setTransform("transform");
    setProjection("projection");
    //addUniform("tex", &i, Zenith::UniformType::UNIFORM_INT);
}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "color");
    bindAttribute(2, "uv");
    bindAttribute(3, "normal");
}

void StaticShader::loadStaticUniforms() {
    loadIntU(1, 0);
}

#pragma once
#include <IShaderProgram.h>

class StaticShader :
    public Zenith::IShaderProgram
{
public:
    StaticShader();
    ~StaticShader();

protected:
    virtual void construct() override;
    
    virtual void bindAttributes() override;
    
    virtual void loadUniforms() override;

};


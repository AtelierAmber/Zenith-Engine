#pragma once
#include <IShaderProgram.h>

class StaticShader :
    public Zenith::IShaderProgram
{
public:
    StaticShader();
    ~StaticShader();

protected:
    void construct() override;
    
    void bindAttributes() override;

    void loadStaticUniforms() override;

private:

    int i = 0;
};


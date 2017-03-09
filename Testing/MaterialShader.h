#pragma once
#include <IShaderProgram.h>
class MaterialShader :
    public Zenith::IShaderProgram
{
public:
    MaterialShader();
    ~MaterialShader();
protected:
    void construct() override;

    void bindAttributes() override;

    void loadStaticUniforms() override;

};


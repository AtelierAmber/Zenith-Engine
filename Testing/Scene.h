#pragma once
#include <IScene.h>
#include <Model.h>

#include "StaticShader.h"

class Scene :
    public Zenith::IScene {
public:
    Scene();
    ~Scene();

    void build() override;

    void enter() override;

    void render() override;

    void update() override;

    void exit() override;

    void destroy() override;

private:
    float m_ticker = 0.0f;

    unsigned int m_shader;
    Zenith::Model m_model;
};


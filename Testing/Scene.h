#pragma once
#include <IScene.h>

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

};


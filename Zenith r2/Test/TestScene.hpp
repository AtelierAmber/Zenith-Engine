#pragma once
#include <scenes/IScene.hpp>

class TestScene :
    public zen::IScene {
public:
    TestScene();
    ~TestScene();
protected:
    virtual void build() override;

    virtual void resume() override;

    virtual void render() override;

    virtual void tick(unsigned long gameTime) override;
    virtual void update(float deltaTime) override;

    virtual void pause() override;

    virtual void destroy() override;

private:
    unsigned long m_prevGameTime = 0;
};


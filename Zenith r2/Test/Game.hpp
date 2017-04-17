#pragma once
#include <scenes/IEngine.hpp>

class Game :
    public zen::IEngine {
public:
    Game();
    ~Game() override;
protected:
    void build() override;

    void update(float deltaTime) override;

    void destroy() override;

};


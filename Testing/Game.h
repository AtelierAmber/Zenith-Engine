#pragma once
#include <IGame.h>
class Game :
    public Zenith::IGame {
public:
    Game();
    ~Game();
protected:
    void build() override;


    void IUpdate() override;


    void destroy() override;

};


#pragma once
#include "Interfaces/IGameCore.h"

class CoreGame :
    public Zenith::IGameCore{
public:
    CoreGame(const char* title, int x, int y, int width, int height, unsigned int flags);
    ~CoreGame();

    virtual void onInit() override;

    virtual void addScreens() override;

    virtual void onExit() override;

};


//Tester.h
#pragma once
#include "CoreGame.h"

class Tester {
public:
    Tester();
    ~Tester();

    int begin();
    void end();
private:
    CoreGame m_game;
};
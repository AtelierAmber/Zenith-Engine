//Tester.h
#pragma once
#include <Core/Core.h>

class Tester {
public:
    Tester();
    ~Tester();

    int begin();
    void end();
private:
    Zenith::Core* m_core;
};
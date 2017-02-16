//Tests.cpp
#include "Tester.h"

Tester::Tester() {
    m_core = new Zenith::Core();
}

Tester::~Tester() {

}

int Tester::begin() {
    return m_core->start("Game Tester", 100, 100, 1280, 720, Zenith::WindowFlag::CENTERED);
}

void Tester::end() {
    m_core->dispose();
}
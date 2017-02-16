//Tests.cpp
#include "Tester.h"

Tester::Tester() : m_game("Game", 0, 0, 1080, 720, Zenith::WindowFlag::CENTERED){
    
}

Tester::~Tester() {

}

int Tester::begin() {
    return m_game.run();
}

void Tester::end() {
    
}
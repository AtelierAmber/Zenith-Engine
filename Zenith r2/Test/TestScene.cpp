#include "TestScene.hpp"
#include <cstdio>

TestScene::TestScene() {}

TestScene::~TestScene() {}

void TestScene::build() {
    
}

void TestScene::resume() {
    
}

void TestScene::render() {
    
}

void TestScene::tick(unsigned long gameTime) {
    if(gameTime / 1000 != m_prevGameTime) {
        std::printf("TIme: %us\n", gameTime / 1000);
        m_prevGameTime = gameTime / 1000;
    }
}

void TestScene::update(float deltaTime) {
    
}

void TestScene::pause() {
    
}

void TestScene::destroy() {
    
}
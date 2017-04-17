#include "Game.hpp"
#include "TestScene.hpp"

#include <debug/Logger.hpp>

Game::Game() { zen::Log::setLogFile("Logs/debug.log"); }

Game::~Game() {}

void Game::build() {
    SceneHandle testScene = registerScene<TestScene>(zen::SceneFlag::DEFAULT_FLAGS);
    pushScene(testScene);
}

void Game::update(float deltaTime) {
    
}

void Game::destroy() {
    
}

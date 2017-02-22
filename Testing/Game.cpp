#include "Game.h"
#include "Scene.h"

Game::Game() {}

Game::~Game() {}

void Game::build() {
    m_sceneManager.addScene(new Scene());
}

void Game::IUpdate() {

}

void Game::destroy() {

}
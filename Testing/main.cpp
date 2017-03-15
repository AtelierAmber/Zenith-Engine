#include "Game.h"

#ifdef _DEBUG
#include <vld.h>
#endif

int main(int argc, char** argv) {
    Game game;
    return game.start("Testing", 0, 0, 1028, 720, Zenith::CENTERED | Zenith::CURSOR_HIDDEN | Zenith::CURSOR_TRAP);
}
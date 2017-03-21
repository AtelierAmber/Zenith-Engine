#include <ecs/Manager.hpp>

struct Position : public zen::ecs::Component {

};

int main(int argc, char** args) {
    zen::ecs::Manager manager;
    manager.addEntity<Position>();
}
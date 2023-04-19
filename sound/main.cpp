#include "include/game_engine.h"

//using namespace sf;

int main(){

    auto myGame = std::make_unique<GameEngine>();

    myGame->run();

    return 0;
}

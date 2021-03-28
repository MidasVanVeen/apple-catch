#include "Game.h"

int main() {

    srand (time(NULL));

    //init gameEngine
    Game engine;

    //gameloop
    while (engine.running()) {

        //update
        engine.update();
        //render
        engine.render();

    }

    return 0;
}

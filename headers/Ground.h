#ifndef PLATFORMER_GROUND_H
#define PLATFORMER_GROUND_H

#include "Game.h"

class Ground {
private:
    sf::RectangleShape shape;
    sf::Vector2f pos;
    sf::Vector2f size;

public:
    Ground(float x, float y, float width, float height);

    void drawTo(sf::RenderWindow &window);
};


#endif //PLATFORMER_GROUND_H

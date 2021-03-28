#include "Ground.h"

Ground::Ground(float x, float y, float width, float height) {
    pos.x = x;
    pos.y = y;

    size.x = width;
    size.y = height;

    shape.setPosition(pos.x,pos.y);
    shape.setSize(size);
    shape.setFillColor(sf::Color(0,255,0));
}

void Ground::drawTo(sf::RenderWindow &window) {
    window.draw(this->shape);
}

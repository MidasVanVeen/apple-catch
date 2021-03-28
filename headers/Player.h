#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include "Game.h"

class Player {
private:
    sf::Vector2f pos;
    sf::RectangleShape shape;
    sf::Vector2f size;

    sf::Vector2f vel;
    float acc;
    float jumpforce;

    int score;

    bool leftpressed;
    bool rightpressed;
    bool jumping;

public:
    Player(float x, float y, float width, float height);

    void update();
    void drawTo(sf::RenderWindow &window);

    void jump();
    void cancel_jump();

    void setLeft(bool state);
    void setRight(bool state);

    sf::Vector2f get_Pos();
    sf::Vector2f get_Size();

    void incrementscore();
    int get_Score();
};


#endif //PLATFORMER_PLAYER_H

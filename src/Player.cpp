#include "Player.h"

Player::Player(float x, float y, float width, float height) {
    pos.x = x;
    pos.y = y;
    size.x = width;
    size.y = height;
    vel.x = 5.f;
    vel.y = 0;
    acc = 0.3;
    jumpforce = 16.f;
    score = 0;

    shape.setPosition(pos.x,pos.y);
    shape.setSize(size);
    shape.setFillColor(sf::Color::Blue);

    // variables for movement
    leftpressed = false;
    rightpressed = false;

    jumping = true;
}

void Player::update() {
    /*
     * updates every frame
     */
    if(leftpressed) {
        this->pos.x -= this->vel.x; // Moves left if the left key is pressed
    }
    if(rightpressed) {
        this->pos.x += this->vel.x; // Moves right if the right key is pressed
    }

    this->pos.y += this->vel.y; // Apply velocity if there is any
    this->vel.y += this->acc; // Apply acceleration

    // True if colliding with ground
    if (this->pos.y + this->size.y >= 500.f) {
        this->pos.y = 500.f - this->size.y; // Sets position to position of ground
        this->vel.y = 0; // Sets velocity to 0
        this->jumping = false; // Sets jumping to false
    }

    // Checks for collision with left wall
    if (this->pos.x < 0) {
        this->pos.x = 0;
    }

    // Checks for collision with right wall
    if (this->pos.x + this->size.x > 800) {
        this->pos.x = 800 - this->size.x;
    }

    this->shape.setPosition(this->pos.x,this->pos.y); // updates position of shape
}

void Player::drawTo(sf::RenderWindow &window) {
    /*
     * draws shape to screen, run every frame
     */
    window.draw(this->shape);
}

void Player::setRight(bool state) {
    /*
     * sets rightpressed to a state, used in Game.cpp
     */
    rightpressed = state;
}

void Player::setLeft(bool state) {
    /*
     * sets leftpressed to a state, used in Game.cpp
    */
    leftpressed = state;
}

void Player::jump() {
    /*
     * makes the player jump
     */
    if (!this->jumping) { //Checks if the player is not jumping
        this->jumping = true; //sets jumping to true
        this->vel.y -= this->jumpforce; //applies jumpforce to velocity

    }
}

sf::Vector2f Player::get_Pos() {
    return this->pos;
}

sf::Vector2f Player::get_Size() {
    return this->size;
}

void Player::incrementscore() {
    this->score++;
}

int Player::get_Score() {
    return this->score;
}

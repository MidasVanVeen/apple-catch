#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Ground.h"
#include "Player.h"

using namespace std;

class Game {
private:
    //variables
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    vector<sf::RectangleShape> apples;
    sf::RectangleShape apple;

    sf::Vector2f apple_Size;
    int maxApples;

    sf::Clock clock;

    //private functions
    void initVariables();
    void initWindow();

    void createApple();
    bool checkapple(sf::RectangleShape apple);
    void gameOver();
public:
    //Constructor/destructor
    Game();
    virtual ~Game();

    const bool running();

    void pollEvents();

    void update();
    void render();

    void displayscore();
    void displaytime();
};


#endif //PLATFORMER_GAME_H

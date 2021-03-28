#include "Game.h"

using namespace std;

Ground ground(0.f,500.f,800.f,100.f); // Create Ground element
Player player(0,0,20.f,20.f); // Create player

void Game::initVariables() {
    /*
     * Initiate variables
     */
    this->window = nullptr;
    this->maxApples = 5;
    this->apple_Size.x = 20;
    this->apple_Size.y = 20;
}

void Game::initWindow() {
    /*
     * Create window
     */
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "platformer");

    this->window->setFramerateLimit(60);
}

Game::Game() {
    /*
     * Constructor
     */
    this->initVariables();
    this->initWindow();
}

Game::~Game(){
    /*
     * Deconstructor
     */
    delete this->window;
}

const bool Game::running() {return this->window->isOpen();} // Return if window is running

void Game::pollEvents() {
    /*
     * Handle events
     */
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                if (this->ev.key.code == sf::Keyboard::Left) {
                    player.setLeft(true);
                }
                if (this->ev.key.code == sf::Keyboard::Right) {
                    player.setRight(true);
                }
                if (this->ev.key.code == sf::Keyboard::Up) {
                    player.jump();
                }
                break;
            case sf::Event::KeyReleased:
                if (this->ev.key.code == sf::Keyboard::Left) {
                    player.setLeft(false);
                }
                if (this->ev.key.code == sf::Keyboard::Right) {
                    player.setRight(false);
                }
                break;
        }
    }
}

void Game::update(){
    /*
     * Update every frame
     */
    this->pollEvents();
    if (apples.size() < this->maxApples)
    {this->createApple();}
    for (auto &a : this->apples) {
        sf::Vector2f playerpos = player.get_Pos();
        sf::Vector2f playersize = player.get_Size();
        sf::Vector2f applepos = a.getPosition();
        sf::Vector2f applesize = a.getSize();
        if (playerpos.x < applepos.x + applesize.x &&
            playerpos.x + playersize.x > applepos.x &&
            playerpos.y < applepos.y + applesize.y &&
            playerpos.y + playersize.y > applepos.y &&
            a.getFillColor() == sf::Color::Red)
        {
            a.setFillColor(sf::Color(84,230,255));
            player.incrementscore();
            this->maxApples++;
        }
    }
    player.update();
    if (player.get_Score() >= 20) {
        this->gameOver();
    }
}

void Game::render() {
    /*
     * Renders to display every frame.
     */
    this->window->clear(sf::Color(84,230,255));
    for (auto &a : this->apples) {
        this->window->draw(a);
    }
    player.drawTo(*this->window);
    ground.drawTo(*this->window);
    this->displayscore();
    this->displaytime();
    this->window->display();
}

void Game::createApple() {
    /*
     * Create apple and add to apples vector
     */
    int x = rand() % 760 + 40;
    int y = rand() % 400 + 40;

    this->apple.setPosition(x,y);
    this->apple.setSize(this->apple_Size);
    this->apple.setFillColor(sf::Color::Red);
    this->checkapple(this->apple);

    if (this->checkapple(this->apple)) {
        this->apples.push_back(this->apple);
    }
}

bool Game::checkapple(sf::RectangleShape apple) {
    /*
     * Check if apple is overlapping with any other apple before creation
     */
    sf::Vector2f applepos = apple.getPosition();
    sf::Vector2f applesize = apple.getSize(); for (auto &a : this->apples) {

        int margin = 20;

        sf::Vector2f vectorapplepos = a.getPosition();
        sf::Vector2f vectorapplesize = a.getSize();
        if (applepos.x + applesize.x > vectorapplepos.x - margin &&
            applepos.x < vectorapplesize.x + vectorapplepos.x + margin &&
            applepos.y + applesize.y > vectorapplepos.y - margin &&
            applepos.y < vectorapplesize.y + vectorapplepos.y + margin)
        {
            return false;
        }
    }
    return true;
}

void Game::displayscore() {
    /*
     * Display score to screen
     */
    sf::Text text;
    sf::Font font;

    font.loadFromFile("bin/fonts/ARIALBD.TTF");
    int score = player.get_Score();
    string score_str = "score: " + to_string(score);
    text.setString(score_str);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    this->window->draw(text);
}

void Game::displaytime() {
    /*
     * Displays current time in seconds
     */
    sf::Text text;
    sf::Font font;
    
    font.loadFromFile("bin/fonts/ARIALBD.TTF");
    sf::Time elapsed = this->clock.getElapsedTime();
    
    text.setString(to_string(elapsed.asSeconds()));
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0,30);
    this->window->draw(text);
}

void Game::gameOver() {
    sf::Time elapsed = this->clock.getElapsedTime();

    char name[50];
    cout << "enter name: ";
    cin >> name;

    std::fstream scoreFile;
    scoreFile.open("scores.csv",std::fstream::out | std::fstream::app);
    scoreFile << name << "," << elapsed.asSeconds() << endl;
    scoreFile.close();

    this->window->close();
}


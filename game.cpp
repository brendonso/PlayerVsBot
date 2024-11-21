#include "game.hpp"


Game::Game() {
    loadFiles();
    player = new Player();
    bot = new Player();

}

void Game::update() {
    timer = clock.getElapsedTime().asSeconds();
    switch (input) {
        case Left:
            player->animate("Run", clock);
            if (player->getCompleted() == true) {
                input = Idle;
            }
            break;
        case Right:
            player->animate("Run", clock);
            if (player->getCompleted() == true) {
                //std::cout << "RUN" << std::endl;
                input = Idle;
            }
            break;
        case Attack:
            player->animate("Attack", clock);
            if (player->getCompleted() == true) {
                //std::cout << "PUNCH" << std::endl;
                input = Idle;
            }
            break;
        case Attack2:
            player->animate("Attack2", clock);
            if (player->getCompleted() == true) {
                //std::cout << "PUNCH" << std::endl;
                input = Idle;
            }
            break;
        case Idle:
            //std::cout << "Idle" << std::endl;
            player->animate("Idle", clock);
            player->setCompleted();
            break;

        default:
            //std::cout << "Default" << std::endl;
            player->animate("Idle", clock);
            break;
    }
}

float Game::getTime() {
    return clock.getElapsedTime().asSeconds();
}

Game::~Game() {
    delete player; 
}

void Game::loadFiles() {
    if (!map.loadFromFile("resources/background.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    background.setTexture(map);
}

void Game::movePlayer(Controls control) {
    switch (control) {
        case Left:
            input = Left;
            player->setFlipped(true);
            player->getSprite().move(-10, 0);
            break;
        case Right:
            input = Right;
            player->setFlipped(false);
            player->getSprite().move(10, 0);
            break;
        case Attack:
            input = Attack;
            break;
        case Attack2:
            input = Attack2;
            break;
        default:
            input = Idle;
            break;
    }
}

void Game::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(background, states);
    window.draw(player->getSprite(), states);
}

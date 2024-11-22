#include "game.hpp"

Game::Game() {
    loadFiles();
    player = new Player();
    bot = new Player();
    //scoreboard
}

void Game::update() {
    timer = clock.getElapsedTime().asSeconds();
    runLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    runRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    updatePlayer(runLeft,runRight);
    //need collisions 
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

void Game::setInput(Controls control) {
    switch (control) {
        case Left:
            input = Left;
            storedInput = Left;
            player->setFlipped(true);
            break;
        case Right:
            input = Right;
            storedInput = Right;
            player->setFlipped(false);
            break;
        case Attack:
            input = Attack;
            break;
        case Attack2:
            input = Attack2;
            break;
        case Jump:
            input = Jump;
            break;
        default:
            input = Idle;
            break;
    }
}
void Game::updatePlayer(bool runLeft, bool runRight) {
    player->setHitbox();
    switch (input) {
        case Left:
            player->getSprite().move(-1, 0);
            player->animate("Run", clock);
            if (player->getCompleted() == true && !runLeft) {
                input = Idle;
            }
            break;
        case Right:
            player->getSprite().move(1, 0);
            player->animate("Run", clock);
            if (player->getCompleted() == true && !runRight) {
                input = Idle;
            }
            break;
        case Attack:
            if(runRight) {
               player->getSprite().move(.25, 0); 
            } else if(runLeft) {
                player->getSprite().move(-.25, 0); 
            }
            player->animate("Attack", clock);
            if (player->getCompleted() == true) {
                input = Idle;
            }
            break;
        case Attack2:
            if(runRight) {
               player->getSprite().move(.25, 0); 
            } else if(runLeft) {
                player->getSprite().move(-.25, 0); 
            }
            player->animate("Attack2", clock);
            if (player->getCompleted() == true) {
                input = Idle;
            }
            break;
        case Idle:
            if(runLeft || runRight) {
            input = storedInput;
            break;
            }
            player->animate("Idle", clock);
            player->setCompleted();
            break;
        case Jump:
            player->setJump(runLeft || runRight);
            input = storedInput;
            break;
        default:
            break;
    }
}

void Game::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(background, states);
    window.draw(*player,states);
}

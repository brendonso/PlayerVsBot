#include "game.hpp"

Game::Game() {
    bot = new Player();  
    player = new Player();  
    stats = new Stats();
}

void Game::Start(int selectedMap, bool selectPlayer) {
    delete player;
    delete bot;
    delete stats;
    loadMap(selectedMap);
    player = new Player(selectPlayer);
    bot = new Player(!selectPlayer);
    stats = new Stats();
}


void Game::update() {
    if(!stats->isMatchOver() && (!player->isDead() || !player->isDead()) ) {
    getMovement();
    getBotMovement();
    player->updatePlayer(runLeft, runRight, L_clock, botHitbox);
    bot->updatePlayer(bot_runLeft,bot_runRight, R_clock, playerHitbox);
    stats->updateHealth(player->getHealth(),bot->getHealth());
    }
    stats->updateStats((player->isDead() || bot->isDead()));
}
    
bool Game::isGameover() {
    if(stats->isGameOver()){
        return true;
    }
    return false;
}

void Game::updateCollisions() {
    playerHitbox = player->getHitbox().getGlobalBounds();
    playerAttackBox = player->getAttackbox().getGlobalBounds();
    playerAttackBox2 = player->getAttackbox2().getGlobalBounds();
    botHitbox = bot->getHitbox().getGlobalBounds();
    botAttackBox = bot->getAttackbox().getGlobalBounds();
    botAttackBox2 = bot->getAttackbox2().getGlobalBounds();
    botInBounds = bot->getHitbox().getPosition().x < 870 && bot->getHitbox().getPosition().x > 30;

}

void Game::getBotMovement() {
    if((!player->isDying() && !bot->isDying())) {
        updateCollisions();
        if(bot->getCompleted() == true || bot->getInput() == Idle) {
            if(modeClock.getElapsedTime().asSeconds() > 5) {
            mode = rand() % 5;
            modeClock.restart();
            }
            if (mode == 1 && playerAttackBox2.intersects(botHitbox)) {
                setNinjaMode();
            } else if((mode == 2 || mode == 3) && playerAttackBox.intersects(botHitbox)){
                setAttackMode();
            } else {
                setNormalMode();
            }
            if (botAttackBox.intersects(playerHitbox)) {
                bot->setInput(Attack);
                player->isAttacked(1);
            }
            checkBounds();
        }
    }
}

void Game::setNormalMode() {
    if (playerHitbox.left < botHitbox.left) {
        bot->setInput(Left);
    } else if (playerHitbox.left > botHitbox.left) {
        bot->setInput(Right);
    }
}
void Game::setNinjaMode() {
    if (playerAttackBox.intersects(botHitbox)) {
        if (playerHitbox.left < botHitbox.left && bot->inBounds(-1)) {
            bot->setInput(Left);
            bot->setJump(true);
        } else if (bot->inBounds(1)) {
            bot->setInput(Right);
            bot->setJump(true);
        }
    } else {
        if (playerHitbox.left < botHitbox.left && bot->inBounds(1)) {
            bot->setInput(Right);
        } else if (bot->inBounds(-1)) {
            bot->setInput(Left);
        }
    }
}
void Game::setAttackMode() {
    if (playerAttackBox.intersects(botHitbox)) {
        if (playerHitbox.left < botHitbox.left && bot->inBounds(-1)) {
            bot->setInput(Left);
            bot->setJump(true);
        } else if (bot->inBounds(1)) {
            bot->setInput(Right);
            bot->setJump(true);
        }
    } else {
        if (playerHitbox.left < botHitbox.left && bot->inBounds(1)) {
            bot->setInput(Right);
        } else if (bot->inBounds(-1)) {
            bot->setInput(Left);
        }
    }
}
void Game::checkBounds() {
    if (botHitbox.intersects(playerHitbox) || !botInBounds) {
        if(!botInBounds) {
            if (playerHitbox.left < botHitbox.left) {
                bot->getSprite().move(-2, 0);
            } else if (playerHitbox.left > botHitbox.left) {
                bot->getSprite().move(2, 0);
            }
        } else {
            if (playerHitbox.left < botHitbox.left) {
                bot->getSprite().move(2, 0);
            } else {
                bot->getSprite().move(-2, 0);
            }
        }
    }
}

void Game::getMovement() {
    if((!player->isDying() && !bot->isDying())) {
        runLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        runRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                player->setJump(runLeft || runRight);
        }

    }
}

void Game::setInput(Controls control) {
    if((!player->isDying() && !bot->isDying())) {
        if (control == Attack || control == Attack2) {
            player->setInput(control);
            attackBot(control);
        } else {
            player->setInput(control);
        }
    }
}
void Game::attackBot(Controls type) {
    if (type == Attack && playerAttackBox.intersects(botHitbox)) {
        bot->isAttacked(10);
    } else if (type == Attack2 && playerAttackBox2.intersects(botHitbox)) {
        bot->setFlipped(true);
        bot->setJump(true);
        bot->isAttacked(20);
    }
}

void Game::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(background, states);
    window.draw(*bot,states);
    window.draw(*player,states);
    window.draw(*stats,states);
}

void Game::loadMap(int selectedMap) {
    switch (selectedMap) {
        case 1:
            if (!map1.loadFromFile("resources/background_01.png")) {
                std::cout << "Error loading MAP" << std::endl;
            }
            background.setTexture(map1);
            break;
        case 2:
            if (!map2.loadFromFile("resources/background_02.png")) {
                std::cout << "Error loading MAP" << std::endl;
            }
            background.setTexture(map2);
            break;
        case 3:
            if (!map3.loadFromFile("resources/background_03.png")) {
                std::cout << "Error loading MAP" << std::endl;
            }
            background.setTexture(map3);
            break;
        case 4:
            if (!map4.loadFromFile("resources/background_04.png")) {
                std::cout << "Error loading MAP" << std::endl;
            }
            background.setTexture(map4);
            break;
        case 5:
            if (!map5.loadFromFile("resources/background_05.png")) {
                std::cout << "Error loading MAP" << std::endl;
            }
            background.setTexture(map5);
            break;
        default:
            std::cout << "Error loading MAP" << std::endl;
            break;
    }
    background.setTextureRect(sf::IntRect(100, 100, 1280, 620));
}
#include "game.hpp"

Game::Game() {
    loadFiles();
    bool selectPlayer = true;
    bot = new Player(selectPlayer);  
    player = new Player(!selectPlayer);  
    stats = new Stats();
}
Game::Game(sf::Texture selectMap, bool selectPlayer) {
    background.setTexture(selectMap);
    isPlayer = selectPlayer;
    player = new Player(selectPlayer);  
    bot = new Player(!selectPlayer);  
    stats = new Stats();
}

void Game::update() {
    getMovement();
    player->updatePlayer(runLeft, runRight, L_clock, botHitbox);
    getBotMovement();
    bot->updatePlayer(bot_runLeft,bot_runRight, R_clock, playerHitbox);
    stats->updateData(player->getHealth(),bot->getHealth());
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

Game::~Game() {
    delete player; 
}

void Game::loadFiles() {
    if (!map.loadFromFile("resources/background.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    background.setTexture(map);
}

void Game::getBotMovement() {
    updateCollisions();
    if(bot->getCompleted() == true || bot->getInput() == Idle) {
        if(modeClock.getElapsedTime().asSeconds() > 5) {
        mode = rand() % 4;
        modeClock.restart();
        }
        
        if (mode == 1 && playerAttackBox2.intersects(botHitbox)) {
            setNinjaMode();
        } else if(mode == 2 && playerAttackBox.intersects(botHitbox)){
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
    runLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    runRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player->setJump(runLeft || runRight);
    }
}

void Game::setInput(Controls control) {
    if (control == Attack || control == Attack2) {
        player->setInput(control);
        attackBot(control);
    } else {
        player->setInput(control);
    }
}
void Game::attackBot(Controls type) {
    if (type == Attack && playerAttackBox.intersects(botHitbox)) {
        bot->isAttacked(10);
    } else if (type == Attack2 && playerAttackBox2.intersects(botHitbox)) {
        bot->setFlipped(true);
        bot->setJump(true);
        bot->isAttacked(10);
    }
}

void Game::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(background, states);
    window.draw(*bot,states);
    window.draw(*player,states);
    window.draw(*stats,states);
}

#include "bot.hpp"

Bot::Bot() {
    loadFiles();
    setupFighter();
    setupHitbox();
    setupAttackbox();
    setupAttackbox2();
}

Bot::Bot(float x) {
    position = x;
    loadFiles();
    setupFighter();
    setupHitbox();
    setupAttackbox();
    setupAttackbox2();
}
void Bot::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(Fighter, states);
    window.draw(Hitbox, states);
    window.draw(Attackbox, states);
    window.draw(Attackbox2, states);
}

void Bot::setupFighter() {
    Fighter.setTexture(R_Idle);
    Fighter.setScale(5, 5); 
    Fighter.setPosition(100, 425);
    Fighter.setOrigin(origin.x + 15, origin.y);
}

void Bot::setupHitbox() {
    Hitbox.setSize(sf::Vector2f(75, 80));
    Hitbox.setFillColor(sf::Color(100, 0, 0, 100));
    Hitbox.setOrigin(origin.x + 30, origin.y - 40);
}
void Bot::setupAttackbox() {
    Attackbox.setSize(sf::Vector2f(40, 80));
    Attackbox.setFillColor(sf::Color(200, 100, 0, 100));
    Attackbox.setOrigin(origin.x - 50, origin.y - 40);
}

void Bot::setupAttackbox2() {
    Attackbox2.setSize(sf::Vector2f(500, 80));
    Attackbox2.setFillColor(sf::Color(0, 0, 100, 100));
    Attackbox2.setOrigin(origin.x - 50, origin.y - 40);
}

sf::RectangleShape& Bot::getHitbox() {
        return Hitbox;
}

sf::RectangleShape& Bot::getAttackbox() {
        return Attackbox;
}

sf::RectangleShape& Bot::getAttackbox2() {
        return Attackbox2;
}
void Bot::animate(const std::string& name, sf::Clock& clock) {

    auto& type = animations[name]; 
    int frames = type.frames;
    sf::Texture* texture = type.texture;
    Fighter.setTexture(*texture);
    if (clock.getElapsedTime().asSeconds() >= .05) {
        frame = (frame + 1) % frames;
        Fighter.setTextureRect(sf::IntRect(0, frame * 23, 137, 23));
        clock.restart();
        completed = false;
        if (frame == 0) {
            completed = true;
        }
    }

    if(jumping == true) {
        jump(clock);
    }
}

void Bot::jump(sf::Clock& clock) {
        if(gravity == true && jumps == 0) {
            gravity = false;
            jumping = false;
        }
        if (jumps == 30 && gravity == false) {
            gravity = true;
        }
        if (clock.getElapsedTime().asSeconds() >= (.01)) {
            if (gravity == false && jumping == true) {
                Fighter.move((0+bias), -10);
                jumps += 1;
            } else if (gravity == true && jumping == true){
                Fighter.move((0+bias), 10);
                jumps -= 1;
            }
        }
}

void Bot::setJump(bool isRunning) {
    if(!isRunning) {
        bias = 0;
    }
    jumping = true;
}

void Bot::setFlipped(bool isFlip) {
    if (isFlip) {
        Fighter.setScale(-5, 5);
        Hitbox.setScale(-1, 1);
        Attackbox.setScale(-1, 1);
        Attackbox2.setScale(-1, 1);
        bias = -5;
    } else {
        Fighter.setScale(5, 5); 
        Hitbox.setScale(1, 1);
        Attackbox.setScale(1, 1);
        Attackbox2.setScale(1, 1);
        bias = 5;
    }
}


void Bot::loadFiles() {
    if (!R_Idle.loadFromFile("resources/R/R_Idle.png")) {
        std::cout << "Error loading location resources/R/" << std::endl; 
    }
    R_Attack.loadFromFile("resources/R/R_Attack1.png");
    R_Attack2.loadFromFile("resources/R/R_Attack2.png");
    R_Dead.loadFromFile("resources/R/R_Dead.png");
    R_Run.loadFromFile("resources/R/R_Run.png");
}
void Bot::setHitbox() {
        Hitbox.setPosition(Fighter.getPosition());
        Attackbox.setPosition(Fighter.getPosition());
        Attackbox2.setPosition(Fighter.getPosition());
}

sf::Sprite& Bot::getSprite() {
    return Fighter; 
}

void Bot::idle() {
    Fighter.setTexture(R_Idle);
}

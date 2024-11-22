#include "player.hpp"

Player::Player() {
    loadFiles();
    setupFighter();
    setupHitbox();
    setupAttackbox();
    setupAttackbox2();

}
void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(Fighter, states);
    window.draw(Hitbox, states);
    window.draw(Attackbox, states);
    window.draw(Attackbox2, states);
}

void Player::setupFighter() {
    Fighter.setTexture(L_Idle);
    Fighter.setScale(5, 5); 
    Fighter.setPosition(100, 350);
    Fighter.setOrigin(origin.x + 15, origin.y);
}

void Player::setupHitbox() {
    Hitbox.setSize(sf::Vector2f(75, 100));
    Hitbox.setFillColor(sf::Color(100, 0, 0, 100));
    Hitbox.setOrigin(origin.x + 30, origin.y - 90);
}
void Player::setupAttackbox() {
    Attackbox.setSize(sf::Vector2f(40, 100));
    Attackbox.setFillColor(sf::Color(200, 100, 0, 100));
    Attackbox.setOrigin(origin.x - 50, origin.y - 90);
}

void Player::setupAttackbox2() {
    Attackbox2.setSize(sf::Vector2f(500, 100));
    Attackbox2.setFillColor(sf::Color(0, 0, 100, 100));
    Attackbox2.setOrigin(origin.x - 50, origin.y - 90);
}

sf::RectangleShape& Player::getHitbox() {
        return Hitbox;
}

sf::RectangleShape& Player::getAttackbox() {
        return Attackbox;
}

sf::RectangleShape& Player::getAttackbox2() {
        return Attackbox2;
}
void Player::animate(const std::string& name, sf::Clock& clock) {

    auto& type = animations[name]; 
    int frames = type.frames;
    sf::Texture* texture = type.texture; //refrence

    Fighter.setTexture(*texture);
    //std::cout << timer << std::endl;
    if (clock.getElapsedTime().asSeconds() >= .05) {
        frame = (frame + 1) % frames;
        Fighter.setTextureRect(sf::IntRect(0, frame * 44, 137, 44));
        clock.restart();
        //std::cout << frame << std::endl;
        completed = false;
        if (frame == 0) {
            completed = true;
        }
    }

    if(jumping == true) {
        jump(clock);
    }
}

void Player::jump(sf::Clock& clock) {
        if(gravity == true && jumps == 0) {
            gravity = false;
            jumping = false;
            fall = 0;
            //completed = true;
        }
        if (jumps == 30 && gravity == false) {
            gravity = true;
 
        }
        if (clock.getElapsedTime().asSeconds() >= (.01)) {
            if (gravity == false) {
                Fighter.move((0+bias), -10);
                jumps += 1;
            } else if (gravity == true){
                Fighter.move((0+bias), 10);
                jumps -= 1;
            }
        }


}

void Player::setJump(bool isRunning) {
    if(!isRunning) {
        bias = 0;
    }
    jumping = true;
}

void Player::setFlipped(bool isFlip) {
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


void Player::loadFiles() {
    if (!L_Idle.loadFromFile("resources/L/L_Idle.png")) {
        std::cout << "Error loading location resources/L/" << std::endl; 
    }
    L_Attack.loadFromFile("resources/L/L_Attack1.png");
    L_Attack2.loadFromFile("resources/L/L_Attack2.png");
    L_Dead.loadFromFile("resources/L/L_Dead.png");
    L_Run.loadFromFile("resources/L/L_Run.png");
}
void Player::setHitbox() {
        Hitbox.setPosition(Fighter.getPosition());
        Attackbox.setPosition(Fighter.getPosition());
        Attackbox2.setPosition(Fighter.getPosition());
}

sf::Sprite& Player::getSprite() {
    return Fighter; 
}

void Player::idle() {
    Fighter.setTexture(L_Idle);
}

#include "player.hpp"

Player::Player() {
    loadFiles();
    Fighter.setTexture(L_Idle);
    Fighter.setScale(5, 5); 
    Fighter.setPosition(400, 300);
    Fighter.setOrigin(origin.x + 15, origin.y);
    //origin == center of image 1/2 
    //ADD hitbox attachment for center
}

void Player::animate(const std::string& name, sf::Clock& clock) {
    float timer = clock.getElapsedTime().asSeconds();
    auto& type = animations[name]; 
    int frames = type.frames;
    sf::Texture* texture = type.texture; //refrence

    Fighter.setTexture(*texture);

    //std::cout << timer << std::endl;
    if (timer >= .1) {
        frame = (frame + 1) % frames;
        Fighter.setTextureRect(sf::IntRect(0, frame * 44, 137, 44));
        clock.restart();
        std::cout << frame << std::endl;
        completed = false;
        if (frame == 0) {
            completed = true;
        }
    }

}

void Player::setFlipped(bool isFlip) {
    if (isFlip) {
        Fighter.setScale(-5, 5);
    } else {
        Fighter.setScale(5, 5); 
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

sf::Sprite& Player::getSprite() {
    return Fighter; 
}

void Player::idle() {
    Fighter.setTexture(L_Idle);
}

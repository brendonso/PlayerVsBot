#include "player.hpp"

Player::Player() {
    loadL_Fighter();
    setupFighter();
    setupHitbox();
    setupAttackbox();
    setupAttackbox2();
}

Player::Player(bool isPlayer) : L_Player(isPlayer) {
    setupPlayer();
    setupFighter();
    setupHitbox();
    setupAttackbox();
    setupAttackbox2();
}

void Player::setInput(Controls type) {
    if(type == Left || type == Right) {
        input = type;
        storedInput = type;
    } else {
        input = type;
    }
}

void Player::animate(const std::string& name, sf::Clock& clock) {
    auto& type = animations[name]; 
    int frames = type.frames;
    sf::Texture* texture = type.texture; //refrence
    Fighter.setTexture(*texture);
    if (clock.getElapsedTime().asSeconds() >= fps) {
        frame = (frame + 1) % frames;
        Fighter.setTextureRect(sf::IntRect(0, frame * frameHeight, 137, frameHeight));
        clock.restart();
        completed = false;
        if (frame == 0) {
            completed = true;
        }
    }

    if(jumping == true) {
        jump();
    }
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(Fighter, states);
    //window.draw(Hitbox, states);
    //window.draw(Attackbox, states);
    //window.draw(Attackbox2, states);
}

bool Player::inBounds(float posX) {
    float fighterPos = Hitbox.getPosition().x + posX;
    sf::FloatRect nextHitbox = Hitbox.getGlobalBounds();
    nextHitbox.left += posX;
    isPlayerCollide = nextHitbox.intersects(oppHitbox);

    if(fighterPos < 870 && fighterPos > 30) { 
        if(jumpCollided && isPlayerCollide) { //jumped in the hitbox allow escape
            return true;
        } else if(jumpCollided && !isPlayerCollide) { //outside the hitbox, back to normal
            jumpCollided = false;
        } else if(!isPlayerCollide) {
            return true;
        } 
    }
    return false;
}

bool Player::oppInFront() {
    sf::FloatRect tempOppHitbox = oppHitbox;
    tempOppHitbox.width += 80;
    if(Attackbox.getGlobalBounds().intersects(tempOppHitbox)) {
        return true;
    }
    return false;
}

void Player::jump() {
    if(gravity == true && jumps == 0) {
        gravity = false;
        jumping = false;
        
    }
    if (jumps == 30 && gravity == false) {
        gravity = true;
    }
    if (Clock.getElapsedTime().asSeconds() >= .01) {
        if(inBounds(bias) == true) {
            Fighter.move(bias, 0);
        }
        if(inBounds(bias) != true) {
            jumpCollided = true;
        }
        if (gravity == false && jumping == true) {
            Fighter.move(0, -10);
            jumps += 1;
        } else if (gravity == true && jumping == true){
            Fighter.move(0, 10);
            jumps -= 1;
        }
        Clock.restart();
    } 
}

void Player::setJump(bool isRunning) {
    if(isRunning) {
        if(flipped) {
        bias = -5;
        } else {
        bias = 5;
        }
    } else {
        bias = 0;
    }
    jumping = true;
}

void Player::setFlipped(bool isFlip) {
    flipped = isFlip;
    if (isFlip) {
        Fighter.setScale(-5, 5);
        Hitbox.setScale(-1, 1);
        Attackbox.setScale(-1, 1);
        Attackbox2.setScale(-1, 1);
    } else {
        Fighter.setScale(5, 5); 
        Hitbox.setScale(1, 1);
        Attackbox.setScale(1, 1);
        Attackbox2.setScale(1, 1);
    }
}


void Player::setupPlayer() {
    if (L_Player == false) {
        loadR_Fighter();
    } else if(L_Player == true) {
        loadL_Fighter();
    }
}

void Player::updatePlayer(bool runLeft, bool runRight, sf::Clock& L_clock, sf::FloatRect& Hitbox) {
    setHitbox();
    oppHitbox = Hitbox;
    switch (input) {
        case Left:
            if(inBounds(-1) == true) {
            Fighter.move(-1, 0);
            }
            if(!oppInFront()) {
            setFlipped(true);
            }
            animate("Run", L_clock);
            if (getCompleted() == true && !runLeft) {
                input = Idle;
            }
            break;
        case Right:
            if(inBounds(1) == true) {
            Fighter.move(1, 0);
            }
            if(!oppInFront()) {
            setFlipped(false);
            }
            animate("Run", L_clock);
            if (getCompleted() == true && !runRight) {
                input = Idle;
            }
            break;
        case Attack:
            if(runRight) {
                if(inBounds(.25) == true) {
                Fighter.move(.25, 0);
                }
            } else if(runLeft) {
                if(inBounds(-.25) == true) {
                Fighter.move(-.25, 0);
                }
            }
            animate("Attack", L_clock);
            if (getCompleted() == true) {
                input = Idle;
            }
            break;
        case Attack2:
            if(runRight) {
                if(inBounds(.25) == true) {
                Fighter.move(.25, 0);
                }
            } else if(runLeft) {
                if(inBounds(-.25) == true) {
                Fighter.move(-.25, 0);
                }
            }
            animate("Attack2", L_clock);
            if (getCompleted() == true) {
                input = Idle;
            }
            break;
        case Idle:
            if(runLeft || runRight) {
            input = storedInput;
            break;
            }
            animate("Idle", L_clock);
            setCompleted();
            break;
        case Jump:
            setJump(runLeft || runRight);
            input = storedInput;
            break;
        case Damaged:
            animate("Damaged", L_clock);
            if (getCompleted() == true) {
            input = Idle;
            }
            break;
        case Dead:
            animate("Dead", L_clock);
            if (getCompleted() == true) {
            hasDied = true;
            input = Idle;
            }
            break;
        default:
            break;
    }
}

void Player::isAttacked(int damage) {
    if(dying == false) {
        Health -= damage;
        if(Health <= 0) {
            frame = 0;
            fps = .2;
            input = Dead;
            dying = true;
        } else {
            input = Damaged;
        }
    }
}

void Player::setupFighter() {
    Fighter.setTexture(*animations["Idle"].texture);
    Fighter.setTextureRect(sf::IntRect(0, frameHeight, 137, frameHeight));
    Fighter.setScale(5, 5); 
    Fighter.setPosition(spawnBias, spawnBiasY);
    Fighter.setOrigin(origin.x + originBiasX, origin.y);
}

void Player::setupHitbox() {
    Hitbox.setSize(sf::Vector2f(75, 100));
    Hitbox.setFillColor(sf::Color(100, 0, 0, 100));
    Hitbox.setOrigin(origin.x + 30, originBiasY);
}
void Player::setupAttackbox() {
    Attackbox.setSize(sf::Vector2f(40 + originBiasX, 100));
    Attackbox.setFillColor(sf::Color(200, 100, 0, 100));
    Attackbox.setOrigin(origin.x - 50, originBiasY);
}

void Player::setupAttackbox2() {
    Attackbox2.setSize(sf::Vector2f(500 + originBiasX, 100));
    Attackbox2.setFillColor(sf::Color(0, 0, 100, 100));
    Attackbox2.setOrigin(origin.x - 50, originBiasY);
}

void Player::setHitbox() {
    Hitbox.setPosition(Fighter.getPosition());
    Attackbox.setPosition(Fighter.getPosition());
    Attackbox2.setPosition(Fighter.getPosition());
}

void Player::loadL_Fighter() {
    if (!L_Idle.loadFromFile("resources/L/L_Idle.png")) {
        std::cout << "Error loading location resources/L/" << std::endl; 
    }
    L_Attack.loadFromFile("resources/L/L_Attack1.png");
    L_Attack2.loadFromFile("resources/L/L_Attack2.png");
    L_Dead.loadFromFile("resources/L/L_Dead.png");
    L_Run.loadFromFile("resources/L/L_Run.png");
    animations = L_animations;
    spawnBias = 100;
    spawnBiasY = 350;
    originBiasX = 15;
}

void Player::loadR_Fighter() {
    if (!R_Idle.loadFromFile("resources/R/R_Idle.png")) {
        std::cout << "Error loading location resources/R/" << std::endl; 
    }
    R_Attack.loadFromFile("resources/R/R_Attack1.png");
    R_Attack2.loadFromFile("resources/R/R_Attack2.png");
    R_Dead.loadFromFile("resources/R/R_Dead.png");
    R_Run.loadFromFile("resources/R/R_Run.png");
    animations = R_animations;
    frameHeight = 23;
    spawnBias = 500;
    spawnBiasY = 425;
    originBiasY = -17;
    originBiasX = 20;
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

sf::Sprite& Player::getSprite() {
    return Fighter; 
}





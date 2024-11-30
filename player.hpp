#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include <vector>
#include "game.hpp"

class Player : public sf::Drawable{
public:
    Player();
    Player(bool isPlayer); 
    
    void loadL_Fighter();
    void loadR_Fighter();
    void setupPlayer();
    void setHitbox();
    void setupFighter();
    void setupHitbox();
    void setupAttackbox();
    void setupAttackbox2();

    void animate(const std::string& name, sf::Clock& clock);
    void updatePlayer(bool runLeft, bool runRight, sf::Clock& L_clock, sf::FloatRect& hitbox);

    sf::Sprite& getSprite(); 
    sf::RectangleShape& getHitbox(); 
    sf::RectangleShape& getAttackbox(); 
    sf::RectangleShape& getAttackbox2();
    
    Controls getInput() {return input;}
    bool getCompleted() {return completed;}
    int getHealth() {return Health;}
    bool isJumping() {return jumping;}
    bool isDead() {return hasDied;}
    bool isDying() {return dying;}
    bool inBounds(float posX);

    bool oppInFront();
    void jump();

    void setJump(bool isRunning);
    void setFlipped(bool isFlip);
    void setCompleted() {completed = false;}
    void setFace(bool isFacing) {face = isFacing;}
    void setInput(Controls type);
    void setStoredInput(Controls type);
    void resetFrame() {frame = 0;}
    void isAttacked(int damage);

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    sf::Sprite Fighter;
    sf::RectangleShape Hitbox;
    sf::RectangleShape Attackbox;
    sf::RectangleShape Attackbox2;
    sf::FloatRect oppHitbox;

    bool face = true;
    bool isFacing = true;
    bool L_Player = true;
    bool completed = true;
    bool isPlayerCollide = false;
    bool jumping = false;
    bool jumpCollided = false;
    bool dying = false;
    bool hasDied = false;
    bool gravity = false;
    bool flipped;

    int Health = 250;
    int spawnBias = 15;
    int spawnBiasY = 350;
    int frameHeight = 44;
    int bias = 0;
    int frame = 0;
    int jumps = 0;
    float position = 15;
    float fps = 0.05;
    int originBiasX;
    int originBiasY = -90;

    sf::Vector2f origin;

    Controls input;
    Controls storedInput;

    sf::Texture L_Attack;
    sf::Texture L_Attack2;
    sf::Texture L_Dead;
    sf::Texture L_Idle;
    sf::Texture L_Run;

    sf::Texture R_Attack;
    sf::Texture R_Attack2;
    sf::Texture R_Dead;
    sf::Texture R_Idle;
    sf::Texture R_Run;

    sf::Clock Clock;

    struct data {
        float frames;
        sf::Texture* texture;
    };

    std::map<std::string, data> animations;

    std::map<std::string, data> R_animations = {
        {"Attack", {7.0f, &R_Attack}},
        {"Attack2", {7.0f, &R_Attack2}},
        {"Damaged", {2.0f, &R_Dead}},
        {"Dead", {8.0f, &R_Dead}},
        {"Idle", {5.0f, &R_Idle}},
        {"Run", {6.0f, &R_Run}},
    };

    std::map<std::string, data> L_animations = {
        {"Attack", {6.0f, &L_Attack}},
        {"Attack2", {10.0f, &L_Attack2}},
        {"Damaged", {2.0f, &L_Dead}},
        {"Dead", {12.0f, &L_Dead}},
        {"Idle", {4.0f, &L_Idle}},
        {"Run", {6.0f, &L_Run}},
    };
};

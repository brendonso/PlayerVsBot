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


    void loadFiles();
    void loadL_Fighter();
    void loadR_Fighter();
    void run();
    void idle();
    sf::Sprite& getSprite(); 
    sf::RectangleShape& getHitbox(); 
    sf::RectangleShape& getAttackbox(); 
    sf::RectangleShape& getAttackbox2(); 

    bool inBounds(float posX);
    bool oppInFront();
    bool isJumping() {return jumping;}
    void animate(const std::string& name, sf::Clock& clock);
    void updatePlayer(bool runLeft, bool runRight, sf::Clock& L_clock, sf::FloatRect& hitbox);
    void jump();
    void setJump(bool isRunning);
    void resetFrame() {frame = 0;}
    void setFlipped(bool isFlip);
    bool getCompleted() {return completed;}
    void setCompleted() {completed = false;}
    void setFace(bool isFacing) {face = isFacing;}
    void setInput(Controls type);
    Controls getInput() {return input;}
    void setStoredInput(Controls type);
    void setupPlayer();
    void setHitbox();
    void setupFighter();
    void setupHitbox();
    void setupAttackbox();
    void setupAttackbox2();


    int getHealth() {return Health;}
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
    Controls input;
    Controls storedInput;

    sf::Clock Clock;

    float position = 15;
    int frame = 0;
    int jumps = 0;


    int Health = 250;
    int spawnBias = 15;
    int spawnBiasY = 350;
    int originBiasX;
    int originBiasY = -90;

    int frameHeight = 44;
    std::string prevName;
    float reset = 0;
    bool flipped;

    bool L_Player = true;
    int bias = 0;
    bool completed = true;
    bool isPlayerCollide = false;
    bool jumping = false;
    bool jumpCollided;

    bool gravity = false;
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

    sf::Vector2f origin;

    int health;
    int stam;

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

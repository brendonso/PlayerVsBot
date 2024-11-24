#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include <vector>
#include "game.hpp"
class Bot : public sf::Drawable{
public:
    Bot();
    Bot(float x); 
    void loadFiles();
    void run();
    void idle();
    sf::Sprite& getSprite(); 
    sf::RectangleShape& getHitbox(); 
    sf::RectangleShape& getAttackbox(); 
    sf::RectangleShape& getAttackbox2(); 


    bool isJumping() {return jumping;}
    void animate(const std::string& name, sf::Clock& clock);

    void jump(sf::Clock& clock);
    void setJump(bool isRunning);
    void resetFrame() {frame = 0;}
    void setFlipped(bool isFlip);
    bool getCompleted() {return completed;}
    void setCompleted() {completed = false;}

    void setHitbox();
    void setupFighter();
    void setupHitbox();
    void setupAttackbox();
    void setupAttackbox2();

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
    sf::Sprite Fighter;
    sf::RectangleShape Hitbox;
    sf::RectangleShape Attackbox;
    sf::RectangleShape Attackbox2;
    float position = 15;
    int frame = 0;
    int jumps = 0;
    std::string prevName;
    float reset = 0;
    bool flipped = false;
    bool firstFlip;
    int bias = 5;
    bool completed = true;

    bool jumping = false;

    bool gravity = false;
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

    std::map<std::string, data> animations = {
        {"Attack", {7.0f, &R_Attack}},
        {"Attack2", {7.0f, &R_Attack2}},
        {"Damage", {8.0f, &R_Dead}},
        {"Dead", {8.0f, &R_Dead}},
        {"Idle", {5.0f, &R_Idle}},
        {"Run", {6.0f, &R_Run}},
    };
};

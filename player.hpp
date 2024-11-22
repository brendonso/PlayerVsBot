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
    float fall = 0;
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
    sf::Texture L_Attack; 
    sf::Texture L_Attack2; 
    sf::Texture L_Dead;
    sf::Texture L_Idle;
    sf::Texture L_Run;
    sf::Vector2f origin;

    int health;
    int stam;

    struct data {
        float frames;
        sf::Texture* texture;
    };

    std::map<std::string, data> animations = {
        {"Attack", {10.0f, &L_Attack}},
        {"Attack2", {6.0f, &L_Attack2}},
        {"Damage", {2.0f, &L_Dead}},
        {"Dead", {12.0f, &L_Dead}},
        {"Idle", {4.0f, &L_Idle}},
        {"Run", {6.0f, &L_Run}},
    };
};

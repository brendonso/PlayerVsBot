#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include <vector>
#include "game.hpp"
class Player {
public:
    Player();
    void loadFiles();
    void run();
    void idle();
    sf::Sprite& getSprite(); 
    void animate(const std::string& name, sf::Clock& clock);
    void setFlipped(bool isFlip);
    bool getCompleted() {return completed;}
    void setCompleted() {completed = false;}


private:
    sf::Sprite Fighter;
    int frame;   
    std::string prevName;
    float reset = 0;
    bool flipped = false;
    bool firstFlip;
    bool completed = false;
    sf::Texture L_Attack; 
    sf::Texture L_Attack2; 
    sf::Texture L_Dead;
    sf::Texture L_Idle;
    sf::Texture L_Run;
    sf::Vector2f origin;

    struct data {
        float frames;
        sf::Texture* texture;
    };

    std::map<std::string, data> animations = {
        {"Attack", {10.0f, &L_Attack}},
        {"Attack2", {6.0f, &L_Attack2}},
        {"Dead", {12.0f, &L_Dead}},
        {"Idle", {4.0f, &L_Idle}},
        {"Run", {6.0f, &L_Run}},
    };
};

#pragma once
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class Player;

enum Controls {
    Left = 1,
    Right = 2,
    Attack = 3,
    Attack2 = 4,
    Idle = 5,
    Dead = 6,
    Jump = 7
};

class Game : public sf::Drawable {
public:
    Game();
    ~Game();
    void loadFiles();
    void setInput(Controls controls);
    void selectMap(int num);
    void update();
    void updatePlayer(bool runLeft, bool runRight) ;
    float getTime();

    void setupHealth();
    void setupStam();

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    Player* player; 
    Player* bot; 
    sf::Clock clock;
    bool Start = false;
    bool jumping = false;
    sf::RectangleShape healthBar;
    sf::RectangleShape stamBar;

    sf::Texture map;
    sf::Sprite background;
    Controls input;
    Controls storedInput;
    bool runLeft;
    bool runRight;
    float timer;
};

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
    Dead = 6
};

class Game : public sf::Drawable {
public:
    Game();
    ~Game();
    void loadFiles();
    void movePlayer(Controls controls);
    void selectMap(int num);
    void update();
    float getTime();

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    Player* player; 
    Player* bot; 
    sf::Clock clock;
    bool Start = false;
    sf::Texture map;
    sf::Sprite background;
    Controls input;
    float timer;
};

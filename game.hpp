#pragma once
#include "player.hpp"
#include "bot.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "stats.hpp"
class Player;
class Bot;
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

    void setupStats();

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    Bot* player; 
    Player* bot; 
    Stats* stats; 
    sf::Clock L_clock;
    sf::Clock R_clock;
    sf::Clock statClock;
    bool Start = false;
    bool jumping = false;


    sf::Texture map;
    sf::Sprite background;
    Controls input;
    Controls storedInput;
    bool runLeft;
    bool runRight;
    float timer;
};

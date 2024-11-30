#pragma once
#include "stats.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class Player;

class Game : public sf::Drawable {
public:
    Game();
    
    void Start(int selectedMap, bool selectedPlayer);
    void loadMap(int selectedMap);
    bool isGameover();
    void update(); 

    void getBotMovement();
    void getMovement();
    void setInput(Controls control);
    void attackBot(Controls type);
    void updateCollisions();
    void checkBounds();

    void setNormalMode();
    void setNinjaMode();
    void setAttackMode();
    void setHackerMode();

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    Player* bot; 
    Player* player; 
    Stats* stats; 

    sf::Clock L_clock;
    sf::Clock R_clock;
    sf::Clock modeClock;
    
    sf::Sprite background;

    sf::FloatRect playerHitbox;
    sf::FloatRect playerAttackBox;
    sf::FloatRect playerAttackBox2;
    sf::FloatRect botHitbox;
    sf::FloatRect botAttackBox;
    sf::FloatRect botAttackBox2;

    sf::Texture map1;
    sf::Texture map2;
    sf::Texture map3;
    sf::Texture map4;
    sf::Texture map5;

    int mode;

    Controls randominput;
    bool runLeft; 
    bool runRight;
    bool botInBounds;
    bool bot_runLeft;
    bool bot_runRight;
};

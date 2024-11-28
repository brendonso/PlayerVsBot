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
    Game(sf::Texture selectMap, bool selectPlayer);
    ~Game();
    void loadFiles();
    void updateInput();
    void setInput(Controls control);
    void getMovement();
    void selectMap(int num);
    void update(); 
    void updatePlayer(bool runLeft, bool runRight);
    void updateBot();

    bool isGameover();
    void getBotMovement();
    void setBotInput();
    void attackBot(Controls type);
    float getTime();
    void updateCollisions();
    void handleCollisions();
    void setupStats();
    void handlePlayerBotCollision();
    void handleAttackCollision();
    void handleBotAttackCollision();

    void setNormalMode();
    void setNinjaMode();
    void setAttackMode();

    void checkBounds();
protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    Player* bot; 
    Player* player; 
    Stats* stats; 
    sf::Clock L_clock;
    sf::Clock R_clock;

    sf::Clock botClock;
    sf::Clock statClock;

    sf::Clock modeClock;

    bool Start = false;
    bool jumping = false;
    bool isPlayer;

    sf::Texture map;
    sf::Sprite background;
    
    sf::FloatRect playerHitbox;
    sf::FloatRect playerAttackBox;
    sf::FloatRect playerAttackBox2;
    sf::FloatRect botHitbox;
    sf::FloatRect botAttackBox;
    sf::FloatRect botAttackBox2;

    int mode;

    Controls randominput;
    bool runLeft;
    bool runRight;
    bool botInBounds;
    bool bot_runLeft;
    bool bot_runRight;
    float timer;
};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string.h>
enum Controls {
    Left = 1,
    Right = 2,
    Attack = 3,
    Attack2 = 4,
    Idle = 5,
    Damaged = 6,
    Dead = 7,
    Jump = 8
};

class Stats : public sf::Drawable {
public:
    Stats();

    void setupL_health();
    void setupR_health();
    void setupClock();
    void setupControls();

    void updateStats(bool isDying);
    void updateHealth(int player, int bot);
    void updateLHealth(int health);
    void updateRHealth(int health);

    bool isMatchOver() {return matchOver;}
    bool isGameOver(){return gameOver;}


protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    int L_health;
    int R_health;
    int matchTime;
    int maxTime;
    bool gameOver;
    bool matchOver;

    sf::Font font;
    sf::Text text;
    sf::Text controls;

    sf::RectangleShape L_healthBar;
    sf::RectangleShape L_healthBack;

    sf::RectangleShape R_healthBar;
    sf::RectangleShape R_healthBack;
    
    sf::Clock clock;
};

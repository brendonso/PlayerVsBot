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
    bool updateClock();
    void updateData(int player, int bot);
    void updateLHealth(int health);
    void updateRHealth(int health);

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    int L_health = 250;
    int R_health = 250;
    int matchTime;
    sf::Font font;
    sf::Text text;

    sf::RectangleShape L_healthBar;
    sf::RectangleShape L_healthBack;
    sf::RectangleShape L_stamBar;

    sf::RectangleShape R_healthBar;
    sf::RectangleShape R_healthBack;
    sf::RectangleShape R_stamBar;

    sf::Vector2f origin;

    sf::Clock clock;
};

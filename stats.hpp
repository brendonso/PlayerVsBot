#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string.h>
class Stats : public sf::Drawable {
public:
    Stats();
    void setupL_health();
    void setupR_health();
    void setupClock();
    void updateClock();

    void L_Damage(int damage);

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

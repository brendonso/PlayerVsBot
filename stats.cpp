#include "stats.hpp"

Stats::Stats() {
    setupL_health();
    setupR_health();
    setupClock();

}


void Stats::updateData(int player, int bot) {
    updateLHealth(player);
    updateRHealth(bot);
    updateClock();
}

void Stats::updateLHealth(int health) {
    L_healthBar.setSize(sf::Vector2f(health, 20));
}

void Stats::updateRHealth(int health) {
    R_healthBar.setSize(sf::Vector2f(health, 20));
}

void Stats::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(L_healthBack, states);
    window.draw(L_healthBar, states);
    window.draw(R_healthBack, states);
    window.draw(R_healthBar, states);
    window.draw(text);
}
bool Stats::updateClock() {
    if(matchTime != 0) {
    matchTime = 1 - static_cast <int> (clock.getElapsedTime().asSeconds());
    text.setString(std::to_string(matchTime));
    } else {
        text.setPosition(325,15);
        text.setString("GAME OVER");
        return false;
    }
    return true;
}
void Stats::setupClock() {
    if (!font.loadFromFile("resources/Tiny5.ttf")) {
    std::cout << "open font error";
    }
    text.setFont(font);
    text.setString("test");
    text.setCharacterSize(50);
    text.setPosition(435,25);
}

void Stats::setupL_health() {
    L_healthBar.setSize(sf::Vector2f(L_health, 20));
    L_healthBar.setFillColor(sf::Color::Green);
    L_healthBar.setPosition(75, 100);
    L_healthBack = L_healthBar;
    L_healthBack.setFillColor(sf::Color::Red);
}

void Stats::setupR_health() {
    R_healthBar.setSize(sf::Vector2f(R_health, 20));
    R_healthBar.setFillColor(sf::Color::Green);
    R_healthBar.setPosition(575, 100);
    R_healthBack = R_healthBar;
    R_healthBack.setFillColor(sf::Color::Red);

}

#include "stats.hpp"

Stats::Stats() : maxTime(45), gameOver(false), matchOver(false) {
    setupL_health();
    setupR_health();
    setupClock();
    setupControls();
}

void Stats::updateHealth(int player, int bot) {
    if(!matchOver) {
    updateLHealth(player);
    updateRHealth(bot);
    }
}

void Stats::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(L_healthBack, states);
    window.draw(L_healthBar, states);
    window.draw(R_healthBack, states);
    window.draw(R_healthBar, states);
    window.draw(text);
    window.draw(controls);
}

void Stats::updateStats(bool isDying) {
    matchTime = maxTime - static_cast<int>(clock.getElapsedTime().asSeconds());
    if(matchTime == 0) {
        isDying = true;
    }
    if (matchTime > 0 && L_health > 0 && R_health > 0) {
        text.setString(std::to_string(matchTime));
    }else if ((matchTime == 0  || L_health <= 0 || R_health <= 0) && !matchOver && isDying) {
        text.setPosition(100, 300);
        text.setCharacterSize(130);
        text.setString("GAME OVER");
        matchOver = true;
        maxTime = 9;
        clock.restart();
    } else if (matchTime <= 7 && matchTime > 0 && matchOver) {
        text.setPosition(330, 10);
        text.setCharacterSize(20);
        text.setString("Press 'M' for menu or wait " + std::to_string(matchTime));
    }else if((matchTime == 0 && matchOver)) {
        gameOver = true;
    }
}

void Stats::updateLHealth(int health) {
    if(health > 0) {
        L_health = health;
    } else {
        L_health = 0;
    }
    L_healthBar.setSize(sf::Vector2f(L_health, 20));
}

void Stats::updateRHealth(int health) {
    if(health > 0) {
        R_health = health;
    } else {
        R_health = 0;
    }
    R_healthBar.setSize(sf::Vector2f(R_health, 20));
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

void Stats::setupControls() {
    controls.setFont(font);
    controls.setString("Left & Right Arrow Keys = Move    Space = Jump   Q = Special Attack     E = Punch     M = Menu");
    controls.setCharacterSize(15);
    controls.setPosition(125,565);
}

void Stats::setupL_health() {
    L_healthBar.setSize(sf::Vector2f(250, 20));
    L_healthBar.setFillColor(sf::Color::Green);
    L_healthBar.setPosition(75, 100);
    L_healthBack = L_healthBar;
    L_healthBack.setFillColor(sf::Color::Red);
}

void Stats::setupR_health() {
    R_healthBar.setSize(sf::Vector2f(250, 20));
    R_healthBar.setFillColor(sf::Color::Green);
    R_healthBar.setPosition(575, 100);
    R_healthBack = R_healthBar;
    R_healthBack.setFillColor(sf::Color::Red);

}

#include "menu.hpp"
#include <iostream>

Menu::Menu() : gameStarted(false), isPlayer(true) {
    loadData();
    setupPlayers();
    setupText();
    setupMaps();
}

void Menu::setInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = static_cast<sf::Vector2f> (position);
        if ( player.getGlobalBounds().contains(mouse)) {
            isPlayer = true;
            player.setFillColor(sf::Color::White);
            bot.setFillColor(sf::Color(50, 50, 50, 250));
        } else if (bot.getGlobalBounds().contains(mouse)) {
            isPlayer = false;
            bot.setFillColor(sf::Color::White);
            player.setFillColor(sf::Color(50, 50, 50, 250));
        } else if (start.getGlobalBounds().contains(mouse)) {
            gameStarted = true;
        } else if (map1.getGlobalBounds().contains(mouse)) {
            selectedMap = 1;
        }  else if (map2.getGlobalBounds().contains(mouse)) {
            selectedMap = 2;
        } else if (map3.getGlobalBounds().contains(mouse)) {
            selectedMap = 3;
        }  else if (map4.getGlobalBounds().contains(mouse)) {
            selectedMap = 4;
        } else if (map5.getGlobalBounds().contains(mouse)) {
            selectedMap = 5;
        }
        selectMap();
    }
}

void Menu::selectMap() {
    map1.setFillColor(sf::Color(50, 50, 50, 250));
    map2.setFillColor(sf::Color(50, 50, 50, 250));
    map3.setFillColor(sf::Color(50, 50, 50, 250));
    map4.setFillColor(sf::Color(50, 50, 50, 250));
    map5.setFillColor(sf::Color(50, 50, 50, 250));

    switch (selectedMap) {
        case 1: 
        map1.setFillColor(sf::Color::White); 
        break;
        case 2: 
        map2.setFillColor(sf::Color::White); 
        break;
        case 3: 
        map3.setFillColor(sf::Color::White); 
        break;
        case 4: 
        map4.setFillColor(sf::Color::White); 
        break;
        case 5: 
        map5.setFillColor(sf::Color::White); 
        break;
    }
}

void Menu::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(player, states);

    window.draw(bot, states);
    window.draw(Select, states);

    window.draw(start, states);
    window.draw(Start, states);

    window.draw(border, states);
    window.draw(border2, states);

    window.draw(map1, states);
    window.draw(map2, states);
    window.draw(map3, states);
    window.draw(map4, states);
    window.draw(map5, states);
}
void Menu::setupPlayers() {
    player.setSize({400, 300});
    player.setFillColor(sf::Color(50, 50, 50, 250));
    player.setPosition(100, 100);
    player.setTexture(&L_Idle);
    player.setTextureRect(sf::IntRect(0, 44, 60, 44));

    bot.setSize({300, 210});
    bot.setFillColor(sf::Color(50, 50, 50, 250));
    bot.setPosition(500, 150);
    bot.setTexture(&R_Idle);
    bot.setTextureRect(sf::IntRect(0, 44, 45, 23));

    start.setSize({330, 90});
    start.setFillColor(sf::Color::Green);
    start.setPosition(275, 420);

    border.setSize({800, 10});
    border.setFillColor(sf::Color::White);
    border.setPosition(50, 150);

    border2.setSize({800, 10});
    border2.setFillColor(sf::Color::White);
    border2.setPosition(50, 390);
}

void Menu::setupMaps() {
    map1.setSize({100, 50});
    map1.setPosition(95, 50);
    map1.setTexture(&Map1);
    map1.setFillColor(sf::Color(50, 50, 50, 250));

    map2.setSize({100, 50});
    map2.setPosition(245, 50);
    map2.setTexture(&Map2);
    map2.setFillColor(sf::Color(50, 50, 50, 250));

    map3.setSize({100, 50});
    map3.setPosition(395, 50);
    map3.setTexture(&Map3);
    map3.setFillColor(sf::Color(50, 50, 50, 250));

    map4.setSize({100, 50});
    map4.setPosition(545, 50);
    map4.setTexture(&Map4);
    map4.setFillColor(sf::Color(50, 50, 50, 250));

    map5.setSize({100, 50});
    map5.setPosition(695, 50);
    map5.setTexture(&Map5);
    map5.setFillColor(sf::Color(50, 50, 50, 250));
}

void Menu::setupText() {
    Select.setFont(font);
    Select.setString("Menu Selection");
    Select.setCharacterSize(30);
    Select.setFillColor(sf::Color::White);
    Select.setPosition(350, 10);    

    Start.setFont(font);
    Start.setString("Start Game");
    Start.setCharacterSize(30);
    Start.setFillColor(sf::Color::White);
    Start.setPosition(370, 440);
}

void Menu::loadData() {
    if (!font.loadFromFile("resources/Tiny5.ttf")) {
        std::cout << "open font error";
    }
    if (!R_Idle.loadFromFile("resources/R/R_Idle.png")) {
        std::cout << "Error loading location resources/R/" << std::endl; 
    }
    if (!L_Idle.loadFromFile("resources/L/L_Idle.png")) {
        std::cout << "Error loading location resources/R/" << std::endl; 
    }
    if (!Map1.loadFromFile("resources/background_01.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    if (!Map2.loadFromFile("resources/background_02.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    if (!Map3.loadFromFile("resources/background_03.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    if (!Map4.loadFromFile("resources/background_04.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }
    if (!Map5.loadFromFile("resources/background_05.png")) {
        std::cout << "Error loading background texture!" << std::endl;
    }

}
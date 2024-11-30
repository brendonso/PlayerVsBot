//Copyright Brendon So 2024
#include "game.hpp"
#include "menu.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "PVP Game");

    Menu menu;
    Game game;

    bool inGame = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!inGame) {
                menu.setInput(event, window);
                if (menu.startGame()) {
                    inGame = true;
                    game.Start(menu.getMap(),menu.getPlayer());
                }
            } else {
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            game.setInput(Left);
                            break;
                        case sf::Keyboard::Right:
                            game.setInput(Right);
                            break;
                        case sf::Keyboard::E:
                            game.setInput(Attack);
                            break;
                        case sf::Keyboard::Q:
                            game.setInput(Attack2);
                            break;
                        case sf::Keyboard::Space:
                            game.setInput(Jump);
                            break;
                        case sf::Keyboard::M:
                            inGame = false;
                            menu.reset();
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        window.clear();
        if (!inGame) {
            window.draw(menu);
        } else {
            game.update();
            window.draw(game);
            if(game.isGameover()) {
            inGame = false;
            menu.reset();
            }
        }
        window.display();
    }
}
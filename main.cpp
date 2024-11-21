#include "game.hpp"
#include "player.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PVP");

    Game game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            game.movePlayer(Left);
                            break;
                        case sf::Keyboard::Right:
                            game.movePlayer(Right);
                            break;
                        case sf::Keyboard::E:
                            game.movePlayer(Attack);
                            break;
                        case sf::Keyboard::Q:
                            game.movePlayer(Attack2);
                            break;
                        default: break;
                    }
                }
        }
        window.clear();
        game.update(); 
        window.draw(game);
        window.display();
        
    }
}

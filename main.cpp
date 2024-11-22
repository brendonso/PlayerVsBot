#include "game.hpp"
#include "player.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "PVP");

    Game game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
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

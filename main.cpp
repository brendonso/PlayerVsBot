#include "game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PVP");
    Game test;
    while (window.isOpen()) {
        sf::Event event;
        
        // Event polling loop
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window on 'close' event
            }
        }

        window.clear();  
        window.draw(test);  
        window.display();  
    }
}
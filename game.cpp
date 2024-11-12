#include "game.hpp"

Game::Game() { 
loadFiles();
}

void Game::loadFiles() { 

if (!map1.loadFromFile("resources/background_01.png")) {
    std::cout << "Error with image location";
}
map2.loadFromFile("resources/background_02.png");
map3.loadFromFile("resources/background_03.png");
map4.loadFromFile("resources/background_04.png");
map5.loadFromFile("resources/background_05.png");

L_Attack.loadFromFile("resources/L/L_Attack1.png");
L_Attack2.loadFromFile("resources/L/L_Attack2.png");
L_Dead.loadFromFile("resources/L/L_dead.png");
L_Idle.loadFromFile("resources/L/L_Idle.png");
L_Run.loadFromFile("resources/L/L_Run.png");

R_Attack.loadFromFile("resources/R/R_Attack1.png");
R_Attack2.loadFromFile("resources/R/R_Attack2.png");
R_Dead.loadFromFile("resources/R/R_Dead.png");
R_Idle.loadFromFile("resources/R/R_Idle.png");
R_Run.loadFromFile("resources/R/R_Run.png");


}

void Game::draw(sf::RenderTarget &window, sf::RenderStates states) const {

    sf::Sprite background(map1);
    window.draw(background,states);

}

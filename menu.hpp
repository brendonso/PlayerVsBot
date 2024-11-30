#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu : public sf::Drawable {
public:
    Menu();
    void loadData();
    void setupTitle();
    void setupPlayers();
    void setupText();
    void setupMaps();
    void selectMap();

    void setInput(sf::Event& event, sf::RenderWindow& window);
    void reset() {gameStarted = false;}

    bool startGame() {return gameStarted;}
    bool getPlayer() {return isPlayer;}
    int getMap() {return selectedMap;}

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
    int selectedMap = 1;
    bool gameStarted;
    bool isPlayer; 
    
    sf::RectangleShape player;
    sf::RectangleShape bot;
    sf::RectangleShape start;
    sf::RectangleShape border;
    sf::RectangleShape border2;

    sf::RectangleShape map1;
    sf::RectangleShape map2;
    sf::RectangleShape map3;
    sf::RectangleShape map4;
    sf::RectangleShape map5;

    sf::Texture L_Idle; 
    sf::Texture R_Idle; 
    sf::Texture Map1;
    sf::Texture Map2;
    sf::Texture Map3;
    sf::Texture Map4;
    sf::Texture Map5;

    sf::Font font;
    sf::Text Select;
    sf::Text Start;
};

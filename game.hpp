#include <SFML/Graphics.hpp>
#include <iostream>

class Game  : public sf::Drawable{
    public:
    Game();
    void loadFiles();

    protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override ;
    private:
    sf::Sprite bacgkround;

    sf::Texture map1;
    sf::Texture map2;
    sf::Texture map3;
    sf::Texture map4;
    sf::Texture map5;

    sf::Sprite playerL;

    sf::Texture L_Attack;
    sf::Texture L_Attack2;
    sf::Texture L_Dead;
    sf::Texture L_Idle;
    sf::Texture L_Run;

    sf::Sprite playerR;

    sf::Texture R_Attack;
    sf::Texture R_Attack2;
    sf::Texture R_Dead;
    sf::Texture R_Idle;
    sf::Texture R_Run;
};
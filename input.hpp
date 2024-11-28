class Entity {
public:
    virtual void animate(const std::string& animation, sf::Clock& clock) = 0;
    virtual sf::Sprite& getSprite() = 0;
    virtual void setCompleted() = 0;
    virtual bool getCompleted() const = 0;

    virtual ~Entity() = default;
};

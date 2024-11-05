#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Food {
public:
    explicit Food(const std::string& textureFile);
    virtual ~Food() = default;

    virtual void Relocate();
    virtual void Draw(sf::RenderWindow& window);
    [[nodiscard]] sf::Vector2f GetPosition() const;
    //void Update();

protected:
    sf::Vector2f position;
    sf::Texture texture; //download photo
    sf::Sprite sprite; //show photo on board
    sf::Clock moveClock;
    const sf::Time moveInterval = sf::seconds(5);
};

class NormalFood : public Food {
public:
    explicit NormalFood(const std::string& textureFile) : Food(textureFile) {}
};

class PoisonousFood : public Food {
public:
    explicit PoisonousFood(const std::string& textureFile) : Food(textureFile) {}
};
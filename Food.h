#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Food {
public:
    virtual ~Food() = default;
    virtual void respawn();
    virtual void draw(sf::RenderWindow& window) = 0;
    [[nodiscard]] sf::Vector2f getPosition() const { return position; }

protected:
    sf::Vector2f position;
};

class NormalFood : public Food {
public:
    explicit NormalFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

class PoisonousFood : public Food {
public:
    explicit PoisonousFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
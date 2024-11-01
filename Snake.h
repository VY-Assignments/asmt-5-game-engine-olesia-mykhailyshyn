#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Food.h"

class Snake {
public:
    enum class Direction { Up, Down, Left, Right };

    Snake(const std::string &headTexturePath, const std::string &bodyTexturePath);
    void setDirection(Direction newDirection);
    void move();
    [[nodiscard]] sf::Vector2f getHeadPosition() const;
    bool hasCollidedWithItself() const;
    void draw(sf::RenderWindow &window) const;
    void grow();
    void applyFoodEffect(const Food& food);
    [[nodiscard]] int getScore() const;

private:
    std::vector<sf::Sprite> body;
    Direction currentDirection;
    sf::Texture headTexture;
    sf::Texture bodyTexture;

    void initializeHead();
    void addInitialBodySegment();
};

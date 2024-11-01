#pragma once
#include <vector>
#include "Point.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Food.h"

class Snake {
public:
    enum class Direction { Up, Down, Left, Right };

private:
    std::vector<sf::Sprite> body;
    sf::Texture headTexture;
    sf::Texture bodyTexture;
    Direction currentDirection;
    int minSize;

public:
    Snake(const std::string &headTexturePath, const std::string &bodyTexturePath);
    void setDirection(Direction newDirection);
    void move();
    [[nodiscard]] bool hasCollidedWithItself() const;
    [[nodiscard]] sf::Vector2f getHeadPosition() const;
    void draw(sf::RenderWindow &window) const;
    void grow();
    void applyFoodEffect(const Food& food);
    int getScore() const { return body.size() - minSize; }
};

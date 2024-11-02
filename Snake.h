#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"
#include "Food.h"

class Snake {
public:
    enum class Direction { Up, Down, Left, Right };

    Snake(const std::string &headTexturePath, const std::string &bodyTexturePath);

    int getScore() const;
    int getSize() const;
    void setDirection(Direction newDirection);
    void move();
    void grow();
    void shrink();
    void draw(sf::RenderWindow &window) const;
    bool hasCollidedWithItself() const;
    Point getHeadPosition() const;
    void applyFoodEffect(const Food& food);

private:
    int score;
    int minSize;
    std::vector<sf::Sprite> body;   // Changed to hold sf::Sprite for each body segment
    Direction currentDirection;
    sf::Texture headTexture;
    sf::Texture bodyTexture;
};

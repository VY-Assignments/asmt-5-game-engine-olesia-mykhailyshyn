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
    std::vector<Point> body;
    Direction currentDirection;
    sf::Color color;
    int minSize;

public:
    Snake(int startX, int startY);
    void setDirection(Direction newDirection);
    void move();
    [[nodiscard]] bool hasCollidedWithWall(const Board &board) const;
    [[nodiscard]] bool hasCollidedWithItself() const;
    [[nodiscard]] Point getHeadPosition() const;
    void draw(sf::RenderWindow &window) const;
    void grow();
    void shrink();
    void applyFoodEffect(const Food& food);
    int getScore() const;
};
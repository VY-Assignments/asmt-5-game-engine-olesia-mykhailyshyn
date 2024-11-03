#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Direction { Up, Down, Left, Right };

class Snake {
public:
    Snake();
    void move();
    void growSnake();
    void shrinkSnake();
    void changeDirection(Direction newDirection);
    [[nodiscard]] bool checkCollision() const;
    [[nodiscard]] bool reachedMaxSize() const;
    [[nodiscard]] sf::Vector2f getHeadPosition() const;
    void setFirstFoodEaten();
    [[nodiscard]] int getSize() const;
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Vector2f> segments;
    Direction direction;
    bool grow;
    int size;
    bool firstFoodEaten;
};
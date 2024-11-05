#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Snake {
public:
    Snake();
    void Move();
    void Grow();
    void Shrink();
    void ChangeDirection(Direction newDirection);
    [[nodiscard]] bool Collision() const;
    [[nodiscard]] bool MaxSize() const;
    [[nodiscard]] sf::Vector2f GetHead() const;
    [[nodiscard]] int GetSize() const;
    void Draw(sf::RenderWindow& window);

private:
    std::vector<sf::Vector2f> segments;
    Direction direction;
    bool grow;
    int size;
};
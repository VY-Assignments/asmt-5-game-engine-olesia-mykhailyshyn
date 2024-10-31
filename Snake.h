#pragma once
#include <vector>
#include "Point.h"
#include <SFML/Graphics.hpp>

class Snake {
private:
    std::vector<Point> body;
    sf::Color color;
    int minSize;

public:
    Snake();
    [[nodiscard]] const std::vector<Point>& getBody() const;

    void move(int dx, int dy);
    void grow();
    void shrink();
    [[nodiscard]] bool checkSelfCollision() const;

    void draw(sf::RenderWindow& window) const;

    [[nodiscard]] Point getHead() const;
};

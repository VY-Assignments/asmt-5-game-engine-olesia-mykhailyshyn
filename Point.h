#pragma once

#include <SFML/System/Vector2.hpp>

class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;

    void setX(int x);
    void setY(int y);
    void setPoint(int x, int y);
    [[nodiscard]] sf::Vector2f toVector2f() const {
        return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    }

    [[nodiscard]] bool isEqual(const Point &other) const;
    bool operator==(const Point &other) const;
};
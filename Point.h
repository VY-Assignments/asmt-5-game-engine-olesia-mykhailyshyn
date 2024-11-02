#pragma once
#include <SFML/System/Vector2.hpp>

class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);
    void setPoint(int x, int y);

    bool isEqual(const Point &other) const;
    bool operator==(const Point &other) const;

    // Convert to sf::Vector2f
    sf::Vector2f toVector2f() const;
};

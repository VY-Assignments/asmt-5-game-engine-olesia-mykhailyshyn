#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const { return x; }
int Point::getY() const { return y; }

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setPoint(int x, int y) { this->x = x; this->y = y; }

bool Point::isEqual(const Point &other) const {
    return (x == other.x && y == other.y);
}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

// Convert Point to sf::Vector2f
sf::Vector2f Point::toVector2f() const {
    return sf::Vector2f(static_cast<float>(x * 10), static_cast<float>(y * 10));
}

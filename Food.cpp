#include "Point.h"
#include "Food.h"
#include <SFML/Graphics.hpp>

Food::Food() : position(0, 0) {}

Point Food::getPosition() const {
    return position;
}

void Food::setPosition(int x, int y) {
    position.setPoint(x, y);
}

void NormalFood::draw(sf::RenderWindow &window) const {
    sf::RectangleShape shape(sf::Vector2f(10, 10));
    shape.setPosition(position.getX() * 10, position.getY() * 10);
    shape.setFillColor(sf::Color::Yellow);
    window.draw(shape);
}

void PoisonousFood::draw(sf::RenderWindow &window) const {
    sf::RectangleShape shape(sf::Vector2f(10, 10));
    shape.setPosition(position.getX() * 10, position.getY() * 10);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}
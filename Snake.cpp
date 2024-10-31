#include "Snake.h"

Snake::Snake() : color(sf::Color::Green), minSize(3) {
    body.emplace_back(5, 5);
    body.emplace_back(5, 6);
    body.emplace_back(5, 7);
}

const std::vector<Point>& Snake::getBody() const { return body; }
Point Snake::getHead() const { return body.front(); }

void Snake::move(int dx, int dy) {
    Point newHead(body.front().getX() + dx, body.front().getY() + dy);
    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
    color = sf::Color::Yellow;
}

void Snake::shrink() {
    if (body.size() > minSize) {
        body.pop_back();
        color = sf::Color::Red;
    }
}

bool Snake::checkSelfCollision() const {
    const Point& head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (head.isEqual(body[i])) return true;
    }
    return false;
}

void Snake::draw(sf::RenderWindow& window) const {
    for (const auto& segment : body) {
        sf::RectangleShape rectangle(sf::Vector2f(10, 10));
        rectangle.setPosition(segment.getX() * 10, segment.getY() * 10);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }
}
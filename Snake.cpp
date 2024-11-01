#include "Snake.h"

Snake::Snake(int startX, int startY) : currentDirection(Direction::Right), color(sf::Color::Green), minSize(1) {
    body.emplace_back(startX, startY);
}

void Snake::setDirection(Direction newDirection) {
    if ((currentDirection == Direction::Up && newDirection != Direction::Down) ||
        (currentDirection == Direction::Down && newDirection != Direction::Up) ||
        (currentDirection == Direction::Left && newDirection != Direction::Right) ||
        (currentDirection == Direction::Right && newDirection != Direction::Left)) {
        currentDirection = newDirection;
    }
}

void Snake::move() {
    Point head = body.front();
    int boardWidth = 40;
    int boardHeight = 40;

    switch (currentDirection) {
        case Direction::Up:    head.setPoint(head.getX(), (head.getY() - 1 + boardHeight) % boardHeight); break;
        case Direction::Down:  head.setPoint(head.getX(), (head.getY() + 1) % boardHeight); break;
        case Direction::Left:  head.setPoint((head.getX() - 1 + boardWidth) % boardWidth, head.getY()); break;
        case Direction::Right: head.setPoint((head.getX() + 1) % boardWidth, head.getY()); break;
    }

    body.insert(body.begin(), head);

    if (body.size() > 2) {
        body.pop_back();
    }
}

bool Snake::hasCollidedWithWall(const Board &board) const {
    return false;
}

bool Snake::hasCollidedWithItself() const {
    Point head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) return true;
    }
    return false;
}

Point Snake::getHeadPosition() const {
    return body.front();
}

void Snake::draw(sf::RenderWindow &window) const {
    for (const auto &segment : body) {
        sf::RectangleShape shape(sf::Vector2f(10, 10));
        shape.setPosition(segment.getX() * 10, segment.getY() * 10);
        shape.setFillColor(color);
        window.draw(shape);
    }
}

void Snake::grow() {
    if (body.size() < 2) {
        body.push_back(body.back());
        color = sf::Color::Green;
    }
}

void Snake::shrink() {
    while (body.size() > 1) {
        body.pop_back();
    }
    color = sf::Color::Red;
}

void Snake::applyFoodEffect(const Food& food) {
    if (food.isPoisonous()) {
        shrink();
    } else {
        grow();
    }
}

int Snake::getScore() const {
    return body.size() - minSize;
}
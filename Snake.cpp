#include "Snake.h"

Snake::Snake(const std::string &headTexturePath, const std::string &bodyTexturePath)
        : score(0), minSize(1), currentDirection(Direction::Right) {

    headTexture.loadFromFile(headTexturePath);
    bodyTexture.loadFromFile(bodyTexturePath);

    sf::Sprite headSegment;
    headSegment.setTexture(headTexture);
    headSegment.setPosition(20 * 10, 20 * 10);
    body.push_back(headSegment);

    sf::Sprite bodySegment;
    bodySegment.setTexture(bodyTexture);
    bodySegment.setPosition(19 * 10, 20 * 10);
    body.push_back(bodySegment);
}

int Snake::getScore() const {
    return score;
}

int Snake::getSize() const {
    return static_cast<int>(body.size());
}

void Snake::setDirection(Direction newDirection) {
    currentDirection = newDirection;
}

void Snake::move() {
    for (size_t i = body.size() - 1; i > 0; --i) {
        body[i].setPosition(body[i - 1].getPosition());
    }

    sf::Vector2f newPos = body[0].getPosition();
    switch (currentDirection) {
        case Direction::Up:    newPos.y -= 10; break;
        case Direction::Down:  newPos.y += 10; break;
        case Direction::Left:  newPos.x -= 10; break;
        case Direction::Right: newPos.x += 10; break;
    }
    body[0].setPosition(newPos);
}

void Snake::grow() {
    sf::Sprite newSegment;
    newSegment.setTexture(bodyTexture);
    newSegment.setPosition(body.back().getPosition());
    body.push_back(newSegment);
    score++;  // Increment score when the snake grows
}

void Snake::shrink() {
    if (body.size() > minSize) {
        body.pop_back();
        score--;  // Decrement score when the snake shrinks
    }
}

void Snake::applyFoodEffect(const Food& food) {
    if (food.isPoisonous()) {
        shrink();
    } else {
        grow();
    }
}

Point Snake::getHeadPosition() const {
    sf::Vector2f pos = body[0].getPosition();
    return Point(static_cast<int>(pos.x / 10), static_cast<int>(pos.y / 10));
}

bool Snake::hasCollidedWithItself() const {
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[0].getGlobalBounds().intersects(body[i].getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

void Snake::draw(sf::RenderWindow &window) const {
    for (const auto &segment : body) {
        window.draw(segment);
    }
}

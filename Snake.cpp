#include "Snake.h"
#include <stdexcept>

Snake::Snake(const std::string &headTexturePath, const std::string &bodyTexturePath)
        : currentDirection(Direction::Right) {
    if (!headTexture.loadFromFile(headTexturePath)) {
        throw std::runtime_error("Failed to load head texture");
    }
    if (!bodyTexture.loadFromFile(bodyTexturePath)) {
        throw std::runtime_error("Failed to load body texture");
    }

    initializeHead();
    addInitialBodySegment();
}

void Snake::initializeHead() {
    sf::Sprite headSegment;
    headSegment.setTexture(headTexture);
    headSegment.setScale(10.f / headTexture.getSize().x, 10.f / headTexture.getSize().y);
    headSegment.setPosition(200, 200);
    body.push_back(headSegment);
}

void Snake::addInitialBodySegment() {
    sf::Sprite bodySegment;
    bodySegment.setTexture(bodyTexture);
    bodySegment.setScale(10.f / bodyTexture.getSize().x, 10.f / bodyTexture.getSize().y);
    bodySegment.setPosition(190, 200);
    body.push_back(bodySegment);
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

sf::Vector2f Snake::getHeadPosition() const {
    return body[0].getPosition();
}

bool Snake::hasCollidedWithItself() const {
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[0].getGlobalBounds().intersects(body[i].getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

void Snake::grow() {
    sf::Sprite newSegment;
    newSegment.setTexture(bodyTexture);
    newSegment.setScale(10.f / bodyTexture.getSize().x, 10.f / bodyTexture.getSize().y);
    newSegment.setPosition(body.back().getPosition());
    body.push_back(newSegment);
}

void Snake::draw(sf::RenderWindow &window) const {
    for (const auto &segment : body) {
        window.draw(segment);
    }
}

void Snake::applyFoodEffect(const Food& food) {
    if (food.isPoisonous()) {
        if (body.size() > 1) {
            body.pop_back();
        }
    } else {
        grow();
    }
}
int Snake::getScore() const {
    return static_cast<int>(body.size() - 1);
}
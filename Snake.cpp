#include "Snake.h"

Snake::Snake(const std::string &headTexturePath, const std::string &bodyTexturePath)
        : currentDirection(Direction::Right), minSize(1)
{
    // Load textures
    if (!headTexture.loadFromFile(headTexturePath)) {
        throw std::runtime_error("Failed to load head texture");
    }
    if (!bodyTexture.loadFromFile(bodyTexturePath)) {
        throw std::runtime_error("Failed to load body texture");
    }

    // Initialize head
    sf::Sprite headSegment;
    headSegment.setTexture(headTexture);
    headSegment.setPosition(20 * 10, 20 * 10); // Initial position
    body.push_back(headSegment); // Add head to body

    // Add initial body segment
    sf::Sprite bodySegment;
    bodySegment.setTexture(bodyTexture);
    bodySegment.setPosition(19 * 10, 20 * 10); // Position next to head
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
    // Move the body by shifting each segment to the position of the one before it
    for (size_t i = body.size() - 1; i > 0; --i) {
        body[i].setPosition(body[i - 1].getPosition());
    }

    // Move the head based on current direction
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
    // Only called when eating normal food
    sf::Sprite newSegment;
    newSegment.setTexture(bodyTexture);  // Use body texture
    newSegment.setPosition(body.back().getPosition()); // Start at the last position
    body.push_back(newSegment);
}

void Snake::draw(sf::RenderWindow &window) const {
    for (const auto &segment : body) {
        window.draw(segment);
    }
}

sf::Vector2f Snake::getHeadPosition() const {
    return body[0].getPosition();
}

bool Snake::hasCollidedWithItself() const {
    const auto &headPos = body[0].getPosition();
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i].getPosition() == headPos) {
            return true;
        }
    }
    return false;
}

void Snake::applyFoodEffect(const Food &food) {
    if (!food.isPoisonous()) {
        grow();
    }
}

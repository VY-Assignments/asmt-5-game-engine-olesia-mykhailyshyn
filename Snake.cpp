#include "Snake.h"

//Snake::Snake() : direction(Right), grow(false), size(1), firstFoodEaten(false) {
Snake::Snake() : direction(Right), grow(false), size(1) {
    segments.emplace_back( 50, 50 );
}

void Snake::Move() {
    sf::Vector2f nextPosition = segments[0];
    switch (direction) {
        case Up: {
            nextPosition.y -= 50; break;
        }
        case Down: {
            nextPosition.y += 50; break;
        }
        case Left: {
            nextPosition.x -= 50; break;
        }
        case Right: {
            nextPosition.x += 50; break;
        }
    }

    if (nextPosition.x < 0) {
        nextPosition.x = 1500 - 50;
    }
    else if (nextPosition.x >= 1500) {
        nextPosition.x = 0;
    }
    if (nextPosition.y < 0) {
        nextPosition.y = 1000 - 50;
    }
    else if (nextPosition.y >= 1000) {
        nextPosition.y = 0;
    }

    if (grow) {
        segments.insert(segments.begin(), nextPosition);
        grow = false;
    }
    else {
        segments.insert(segments.begin(), nextPosition);
        segments.pop_back();
    }
}

void Snake::Grow() {
    grow = true;
}

void Snake::Shrink() {
    if (segments.size() > 1) {
        segments.pop_back();
        --size;
    }
}

bool Snake::MaxSize() const {
    return size >= 200;
}

sf::Vector2f Snake::GetHead() const {
    return segments[0];
}

void Snake::Draw(sf::RenderWindow& window) {
    sf::RectangleShape segmentShape(sf::Vector2f(50, 50));
    segmentShape.setFillColor(sf::Color(128, 0, 128));
    for (const auto& segment : segments) {
        segmentShape.setPosition(segment);
        window.draw(segmentShape);
    }
}

void Snake::ChangeDirection(Direction newDirection) {
    if ((direction == Up && newDirection != Down) ||
        (direction == Down && newDirection != Up) ||
        (direction == Left && newDirection != Right) ||
        (direction == Right && newDirection != Left)) {
        direction = newDirection;
    }
}

//void Snake::SetFirstFoodEaten() {
//    firstFoodEaten = true;
//}

bool Snake::Collision() const {
    sf::Vector2f headPosition = segments[0];
    for (size_t i = 1; i < segments.size(); i++) {
        if (segments[i] == headPosition) {
            return true;
        }
    }
    return false;
}

int Snake::GetSize() const {
    return segments.size();
}
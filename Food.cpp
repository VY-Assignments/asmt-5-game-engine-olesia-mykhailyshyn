#include "Point.h"
#include "Food.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

Food::Food() : position(0, 0) {}

Point Food::getPosition() const {
    return position;
}

void Food::setPosition(int x, int y) {
    position.setPoint(x, y);
}

NormalFood::NormalFood() {
    setPosition(rand() % 40, rand() % 40);
    if (!texture.loadFromFile("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/normal.png")) {
        throw std::runtime_error("Failed to load normal food texture");
    }
}

void NormalFood::draw(sf::RenderWindow &window) const {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(10.f / texture.getSize().x, 10.f / texture.getSize().y);
    sprite.setPosition(position.getX() * 10, position.getY() * 10);
    window.draw(sprite);
}

PoisonousFood::PoisonousFood() {
    setPosition(rand() % 40, rand() % 40);
    if (!texture.loadFromFile("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/poisonous.png")) {
        throw std::runtime_error("Failed to load poisonous food texture");
    }
}
void PoisonousFood::draw(sf::RenderWindow &window) const {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(10.f / texture.getSize().x, 10.f / texture.getSize().y);  // Scale to 10x10 pixels
    sprite.setPosition(position.getX() * 10, position.getY() * 10);
    window.draw(sprite);
}

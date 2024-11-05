#include "Food.h"
#include <cstdlib> //random

Food::Food(const std::string& textureFile) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(static_cast<float>(50) / texture.getSize().x, static_cast<float>(50) / texture.getSize().y);
    Relocate();
}

void Food::Relocate() {
    position.x = (std::rand() % (1500 / 50)) * 50;
    position.y = (std::rand() % (1000 / 50)) * 50;
}

void Food::Draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

//void Food::Update() {
//    if (moveClock.getElapsedTime() > moveInterval) {
//        Relocate();
//        moveClock.restart();
//    }
//}

sf::Vector2f Food::GetPosition() const {
    return position;
}
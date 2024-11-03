#include "Food.h"
#include <stdexcept>

void Food::respawn() {}

NormalFood::NormalFood(const std::string& textureFile) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(
            static_cast<float>(50) / texture.getSize().x,
            static_cast<float>(50) / texture.getSize().y
    );
    respawn();
}

void NormalFood::respawn() {
    position.x = (std::rand() % (1500 / 50)) * 50;
    position.y = (std::rand() % (1000 / 50)) * 50;
}

void NormalFood::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

PoisonousFood::PoisonousFood(const std::string& textureFile) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(
            static_cast<float>(50) / texture.getSize().x,
            static_cast<float>(50) / texture.getSize().y
    );
    respawn();
}

void PoisonousFood::respawn() {
    position.x = (std::rand() % (1500 / 50)) * 50;
    position.y = (std::rand() % (1000 / 50)) * 50;
}

void PoisonousFood::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

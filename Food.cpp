#include "Food.h"
#include <cstdlib>

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

// Реалізація MovingFood
MovingFood::MovingFood(const std::string& textureFile) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(
            static_cast<float>(50) / texture.getSize().x,
            static_cast<float>(50) / texture.getSize().y
    );
    respawn();
}

void MovingFood::respawn() {
    position.x = (std::rand() % (1500 / 50)) * 50;
    position.y = (std::rand() % (1000 / 50)) * 50;
}

void MovingFood::move() {
    // Переміщуємо їжу на випадкову позицію
    position.x += ((std::rand() % 3) - 1) * 50;  // Рух вліво, вправо або залишитися
    position.y += ((std::rand() % 3) - 1) * 50;  // Рух вгору, вниз або залишитися

    // Переконуємося, що позиція їжі залишається в межах екрану
    position.x = std::max(0.f, std::min(position.x, 1500.f - 50));
    position.y = std::max(0.f, std::min(position.y, 1000.f - 50));
}

void MovingFood::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

// Реалізація TimedFood
TimedFood::TimedFood(const std::string& textureFile) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(
            static_cast<float>(50) / texture.getSize().x,
            static_cast<float>(50) / texture.getSize().y
    );
    respawn();
}

void TimedFood::respawn() {
    position.x = (std::rand() % (1500 / 50)) * 50;
    position.y = (std::rand() % (1000 / 50)) * 50;
    lifespanClock.restart();  // Перезапускаємо таймер життя їжі
}

bool TimedFood::shouldDespawn() const {
    return lifespanClock.getElapsedTime() > lifespan;
}

void TimedFood::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Food {
public:
    virtual ~Food() = default;
    virtual void respawn();
    virtual void draw(sf::RenderWindow& window) = 0;
    [[nodiscard]] sf::Vector2f getPosition() const { return position; }

protected:
    sf::Vector2f position;
};

class NormalFood : public Food {
public:
    explicit NormalFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

class PoisonousFood : public Food {
public:
    explicit PoisonousFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

// Новий клас для рухомої їжі
class MovingFood : public Food {
public:
    explicit MovingFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;
    void move();  // Метод для руху

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

// Новий клас для тимчасової їжі
class TimedFood : public Food {
public:
    explicit TimedFood(const std::string& textureFile);
    void respawn() override;
    void draw(sf::RenderWindow& window) override;
    bool shouldDespawn() const;  // Метод для перевірки, чи потрібно видалити їжу

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock lifespanClock;
    const sf::Time lifespan = sf::seconds(10);  // Їжа зникає через 10 секунд
};

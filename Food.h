#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Food {
protected:
    Point position;

public:
    Food();
    virtual ~Food() = default;
    [[nodiscard]] virtual bool isPoisonous() const = 0;
    [[nodiscard]] Point getPosition() const;
    void setPosition(int x, int y);
    virtual void applyEffect() = 0;
    virtual void draw(sf::RenderWindow &window) const = 0;
};

class NormalFood : public Food {
    sf::Texture texture;
public:
    NormalFood();
    [[nodiscard]] bool isPoisonous() const override { return false; }
    void applyEffect() override {}
    void draw(sf::RenderWindow &window) const override;
};

class PoisonousFood : public Food {
    sf::Texture texture;
public:
    PoisonousFood();
    [[nodiscard]] bool isPoisonous() const override { return true; }
    void applyEffect() override {}
    void draw(sf::RenderWindow &window) const override;
};

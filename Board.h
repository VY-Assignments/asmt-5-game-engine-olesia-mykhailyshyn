#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Food.h"
#include <vector>

class Board {
private:
    int width;
    int height;
    sf::RenderWindow &window;
    std::vector<Food *> foods;

public:
    Board(int w, int h, sf::RenderWindow &win);
    ~Board();
    void addFood(Food *food);
    void clear();
    void draw() const;
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] const std::vector<Food*>& getFoods() const;
    void removeFood(Food *food);
    [[nodiscard]] bool isWithinBounds(const sf::Vector2f &position) const;
    [[nodiscard]] sf::RenderWindow& getWindow() const { return window; }
};
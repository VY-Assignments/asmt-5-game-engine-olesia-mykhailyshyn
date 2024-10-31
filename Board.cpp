#include <SFML/Graphics.hpp>
#include "Food.h"
#include <vector>
#include "Board.h"

Board::Board(int w, int h, sf::RenderWindow &win) : width(w), height(h), window(win) {}

Board::~Board() {
    for (auto food : foods) {
        delete food;
    }
    foods.clear();
}

void Board::addFood(Food *food) {
    foods.push_back(food);
}

void Board::clear() {
    window.clear(sf::Color::Black);
}

void Board::draw() const {
    sf::RectangleShape line(sf::Vector2f(width * 10, 1));
    line.setFillColor(sf::Color(50, 50, 50));

    for (int i = 0; i <= height; ++i) {
        line.setPosition(0, i * 10);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, height * 10));
    for (int i = 0; i <= width; ++i) {
        line.setPosition(i * 10, 0);
        window.draw(line);
    }

    for (const auto &food : foods) {
        food->draw(window);
    }

    window.display();
}
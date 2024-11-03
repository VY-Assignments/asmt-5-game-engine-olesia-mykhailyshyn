#include "GameRenderer.h"

GameRenderer::GameRenderer(Game& game) : game(game) {}

void GameRenderer::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 50));
    drawGrid(window);
    game.snake.draw(window);

    for (const auto& food : game.foods) {
        food->draw(window);
    }

    drawShadows(window);
    game.weather.render(window);
    window.display();
}

void GameRenderer::drawGrid(sf::RenderWindow& window) {
    const int WIDTH = 1500;
    const int HEIGHT = 1000;
    const int SIZE = 50;

    for (int x = 0; x < WIDTH; x += SIZE) {
        for (int y = 0; y < HEIGHT; y += SIZE) {
            sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(75, 0, 130));
            window.draw(cell);
        }
    }
}

void GameRenderer::drawShadows(sf::RenderWindow& window) {
    for (const auto& shadow : game.shadows) {
        window.draw(shadow);
    }
}
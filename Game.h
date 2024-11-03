#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"
#include "InputHandler.h"

class Game {
public:
    explicit Game(const std::string& playerName);
    void run(sf::RenderWindow& window);
    [[nodiscard]] int getFinalScore() const;

private:
    void update();
    void render(sf::RenderWindow& window);
    void handleCommand(Command command);
    static void drawGrid(sf::RenderWindow& window);

    Snake snake;
    std::unique_ptr<Food> normalFood;
    std::unique_ptr<Food> poisonousFood;
    std::string playerName;
    bool gameOver = false;
};
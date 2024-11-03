#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"
#include "InputHandler.h"
#include "Weather.h"
#include <vector>
#include <string>
#include <memory>

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

    void maintainFoodCount();
    void respawnAllFood();
    void updateShadows();
    void drawShadows(sf::RenderWindow& window);

    Snake snake;
    std::vector<std::unique_ptr<Food>> foods;
    std::vector<sf::CircleShape> shadows;
    Weather weather;

    std::string playerName;
    bool gameOver = false;
    const int maxFoodCount = 7;
    sf::Clock foodRespawnTimer;
    sf::Clock shadowTimer;
    sf::Time shadowUpdateInterval = sf::seconds(5);
};
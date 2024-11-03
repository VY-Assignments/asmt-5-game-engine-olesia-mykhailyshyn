#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"
#include "InputHandler.h"

enum class FoodBehavior {
    Static,
    Moving,
    Timed
};

class Game {
public:
    explicit Game(const std::string& playerName);
    void run(sf::RenderWindow& window);
    int getFinalScore() const;

private:
    void update();
    void render(sf::RenderWindow& window);
    void handleCommand(Command command);
    static void drawGrid(sf::RenderWindow& window);
    void updateShadows();
    void drawShadows(sf::RenderWindow& window);
    void updateFood();

    Snake snake;
    std::vector<std::unique_ptr<Food>> foods;
    std::string playerName;
    bool gameOver = false;

    // Тіньові ділянки
    std::vector<sf::CircleShape> shadows;
    sf::Clock shadowTimer;
    const sf::Time shadowUpdateInterval = sf::seconds(2);

    sf::Clock foodSpawnTimer;
    const sf::Time foodSpawnInterval = sf::seconds(5);
};

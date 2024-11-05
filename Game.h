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
    void Run(sf::RenderWindow& window);
    [[nodiscard]] int GetFinalScore() const;

    Snake snake;
    Weather weather;
    std::vector<sf::CircleShape> shadows;
    std::vector<std::unique_ptr<Food>> foods;

private:
    void Update();
    void HandleCommand(Command command);
    void FoodCount();
    void RelocateFood();
    void UpdateShadows();

    std::string playerName;
    bool gameOver = false;
    //const int maxFoodCount = 7;
    sf::Clock foodRespawnTimer;
    sf::Clock shadowTimer;
    sf::Time shadowUpdateInterval = sf::seconds(5);
};
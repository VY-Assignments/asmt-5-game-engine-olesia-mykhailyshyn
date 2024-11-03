#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"
#include "InputHandler.h"

class Game {
public:
    explicit Game(const std::string& playerName);
    void run(sf::RenderWindow& window);
    int getFinalScore() const;  // Add this method

private:
    void update();
    void render(sf::RenderWindow& window);
    void handleCommand(Command command);
    static void drawGrid(sf::RenderWindow& window);

    Snake snake;
    NormalFood normalFood{R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\normal.png)"};
    PoisonousFood poisonousFood{R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\poisonous.png)"};
    Scoreboard scoreboard{R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\Scoreboard.txt)"};
    InputHandler inputHandler;
    std::string playerName;
    bool gameOver = false;
};
